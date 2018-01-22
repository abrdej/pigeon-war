#ifndef TURN_H
#define TURN_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>
#include <unordered_set>
#include <managers/players_manager.h>

enum class frequency_types {
	every_turn,
	every_two_turns_from_this,
	every_two_turns_from_next,
	after_n_rounds,
    after_n_turns
};

struct turn_callback_info {
	bool ended{false};
	std::uint32_t callback_id;
};

class turn_system
{
	struct callback_pack {
		callback_pack() = default;
		callback_pack(frequency_types frequency,
					  int32_t duration,
					  std::function<void(turn_callback_info&)> callback)
				: frequency(frequency),
				  callback(std::move(callback)),
				  duration(duration),
				  number_of_calls(0) {}

		frequency_types frequency;
		std::function<void(turn_callback_info&)> callback;
		int32_t duration;
		int32_t number_of_calls;
	};

public:

	static void end_turn();
	static void on_turn(std::uint32_t turn_n, const std::function<void()>& task);

	static std::uint32_t get_callback_id() {
		static std::uint32_t callback_id_gen = 0;
		return callback_id_gen++;
	}

	static std::uint32_t set_callback(const frequency_types& frequency,
									  int32_t duration,
									  const std::function<void(turn_callback_info&)>& callback) {

		std::uint32_t callback_id = get_callback_id();

		callbacks_to_set.emplace_back(callback_id, callback_pack(frequency, duration, callback));

		return callback_id;
	}

	static std::uint32_t set_callback(const frequency_types& frequency,
									  int32_t duration,
									  const std::function<void()>& callback) {

		std::uint32_t callback_id = get_callback_id();

		callbacks_to_set.emplace_back(callback_id, callback_pack(frequency, duration, [callback](turn_callback_info&) {
			callback();
		}));

		return callback_id;
	}

	static void remove_callback(std::uint32_t callback_id) {
		callbacks_to_remove.insert(callback_id);
	}

private:
	static std::uint32_t turn_n;
	static std::unordered_multimap<std::uint32_t, std::function<void()>> tasks;
	static std::unordered_map<std::uint32_t, callback_pack> callbacks;
	static std::unordered_set<std::uint32_t> callbacks_to_remove;
	static std::vector<std::pair<std::uint32_t, callback_pack>> callbacks_to_set;
};

struct callback_deleter {
	void operator()(std::uint32_t* p) const {
		turn_system::remove_callback(*p);
		delete p;
	}
};

//using callback_holder = std::unique_ptr<std::uint32_t, callback_deleter>;
using callback_holder = std::shared_ptr<std::uint32_t>;

inline auto make_callback_holder(std::uint32_t callback_id) {
	return callback_holder(new std::uint32_t(callback_id), callback_deleter());
}

template <typename Callback>
inline auto make_every_turn_callback_holder(std::int32_t duration,
											Callback callback) {

	return make_callback_holder(turn_system::set_callback(frequency_types::every_turn,
														  duration,
														  callback));
}

template <typename Callback>
inline void set_every_turn_callback(std::int32_t duration,
									Callback callback) {

	turn_system::set_callback(frequency_types::every_turn,
							  duration,
							  callback);
}

template <typename Callback>
inline auto make_every_two_turns_from_next_callback_holder(std::int32_t duration,
														   Callback callback) {

	return make_callback_holder(turn_system::set_callback(frequency_types::every_two_turns_from_next,
														  duration,
														  callback));
}

template <typename Callback>
inline auto make_after_n_round_callback_holder(std::int32_t duration,
											   Callback callback) {

	return make_callback_holder(turn_system::set_callback(frequency_types::after_n_rounds,
														  duration,
														  callback));
}

template <typename Callback>
inline auto make_after_n_turns_callback_holder(std::int32_t duration,
                                               Callback callback) {

    return make_callback_holder(turn_system::set_callback(frequency_types::after_n_turns,
                                                          duration,
                                                          callback));
}

template <typename Callback>
inline void set_after_n_round_callback(std::int32_t duration,
									   Callback callback) {

	turn_system::set_callback(frequency_types::after_n_rounds,
							  duration,
							  callback);
}

class turn_callback_helper
{
protected:
	template <typename Callback>
	void on_every_turn(Callback callback) {
		on_every_turn_holder = make_callback_holder(turn_system::set_callback(frequency_types::every_turn, 0, callback));
	}
	template <typename Callback>
	void on_every_two_turns_from_this(Callback callback) {
		on_every_two_turns_from_this_holder = make_callback_holder(turn_system::set_callback(frequency_types::every_two_turns_from_this, 0, callback));
	}
	template <typename Callback>
	void after_player_turn(std::uint32_t entity_id, Callback callback) {
		after_player_turn_holder = make_callback_holder(turn_system::set_callback(frequency_types::every_turn, 0, [entity_id, callback]() {
			if (players_manager::active_player_entity(entity_id)) {
				callback();
			}
		}));
	}
	template <typename Callback>
	void on_every_two_turns_from_next(Callback callback) {
		on_every_two_turns_from_next_holder = make_callback_holder(turn_system::set_callback(frequency_types::every_two_turns_from_next, 0, callback));
	}

private:
	callback_holder on_every_turn_holder;
	callback_holder on_every_two_turns_from_this_holder;
	callback_holder on_every_two_turns_from_next_holder;
	callback_holder after_player_turn_holder;
};

#endif