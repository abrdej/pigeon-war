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
#include <utils/control_ptr.h>
#include <utils/callback_holder.h>
#include <boost/signals2.hpp>

enum class frequency_types {
	every_turn,
	every_two_turns_from_this,
	every_two_turns_from_next,
	after_n_rounds,
	after_n_turns
};

using turn_scoped_connection = boost::signals2::scoped_connection;
using turn_connection = boost::signals2::connection;
using turn_signal = boost::signals2::signal<void()>;
using turn_slot = turn_signal::slot_type;
using extended_turn_slot = turn_signal::extended_slot_type;

struct turn_callback_info {
	bool ended{false};
	turn_connection conn;
};

class turn_system
{
	struct turn_callback_wrapper {
		frequency_types frequency;
		int32_t duration;
		int32_t number_of_calls;
		std::function<void(turn_callback_info&)> callback;

		turn_callback_wrapper(const frequency_types& frequency,
							  int32_t duration,
							  std::function<void(turn_callback_info&)> callback)
				: frequency(frequency),
				  duration(duration),
				  number_of_calls(0),
				  callback(std::move(callback)) {}

		void operator()(const turn_connection& conn) {
			if (frequency == frequency_types::every_turn) {
				turn_callback_info info{duration && ++number_of_calls == duration,
										conn};

				callback(info);

				if (info.ended) {
					conn.disconnect();
				}

			} else if (frequency == frequency_types::every_two_turns_from_this) {
				turn_callback_info info{duration && ++number_of_calls == duration,
										conn};
				callback(info);
				frequency = frequency_types::every_two_turns_from_next;
				if (info.ended) {
					conn.disconnect();
				}

			} else if (frequency == frequency_types::every_two_turns_from_next) {
				frequency = frequency_types::every_two_turns_from_this;

			} else if (frequency == frequency_types::after_n_rounds) {
				if (++number_of_calls == duration * 2) {
					turn_callback_info info{true,
											conn};
					callback(info);
					conn.disconnect();
				}
			} else if (frequency == frequency_types::after_n_turns) {
				if (++number_of_calls == duration) {
					turn_callback_info info{true,
											conn};
					callback(info);
					conn.disconnect();
				}
			}
		}
	};

public:

	static void end_turn();
	static void on_turn(std::uint32_t turn_n, const std::function<void()>& task);

	static std::uint32_t get_callback_id() {
		static std::uint32_t callback_id_gen = 0;
		return callback_id_gen++;
	}

	static turn_scoped_connection set_callback(const frequency_types& frequency,
											 int32_t duration,
											 const std::function<void(turn_callback_info&)>& callback) {

		return turn_scoped_connection(next_turn_signal.connect_extended(turn_callback_wrapper(frequency, duration, callback)));
	}

	static turn_scoped_connection set_callback(const frequency_types& frequency,
											 int32_t duration,
											 const std::function<void()>& callback) {

		return turn_scoped_connection(next_turn_signal.connect_extended(turn_callback_wrapper(frequency, duration,
																							  [callback](turn_callback_info&) {
			return callback();
		})));
	}

private:
	static std::uint32_t turn_n;
	static std::unordered_multimap<std::uint32_t, std::function<void()>> tasks;
	static turn_signal next_turn_signal;
};

template <typename Callback>
inline auto make_every_turn_callback_holder(std::int32_t duration,
											Callback callback) {

    return turn_system::set_callback(frequency_types::every_turn,
									 duration,
									 callback);
}

template <typename Callback>
inline void set_every_turn_callback(std::int32_t duration,
									Callback callback) {

	turn_system::set_callback(frequency_types::every_turn,
							  duration,
							  callback).release();
}

template <typename Callback>
inline auto make_every_two_turns_from_next_callback_holder(std::int32_t duration,
														   Callback callback) {

	return turn_system::set_callback(frequency_types::every_two_turns_from_next,
									 duration,
									 callback);
}

template <typename Callback>
inline auto make_after_n_round_callback_holder(std::int32_t duration,
											   Callback callback) {

	return turn_system::set_callback(frequency_types::after_n_rounds,
									 duration,
									 callback);
}

template <typename Callback>
inline auto make_after_n_turns_callback_holder(std::int32_t duration,
											   Callback callback) {

	return turn_system::set_callback(frequency_types::after_n_turns,
									 duration,
									 callback);
}

template <typename Callback>
inline void set_after_n_round_callback(std::int32_t duration,
									   Callback callback) {

	turn_system::set_callback(frequency_types::after_n_rounds,
							  duration,
							  callback).release();
}

class turn_callback_helper
{
protected:
	template <typename Callback>
	void on_every_turn(Callback callback) {
		on_every_turn_holder = std::move(turn_system::set_callback(frequency_types::every_turn, 0, callback));
	}
	template <typename Callback>
	void on_every_two_turns_from_this(Callback callback) {
		on_every_two_turns_from_this_holder = std::move(turn_system::set_callback(frequency_types::every_two_turns_from_this, 0, callback));
	}
	template <typename Callback>
	void after_player_turn(std::uint32_t entity_id, Callback callback) {
		after_player_turn_holder = std::move(turn_system::set_callback(frequency_types::every_turn, 0, [entity_id, callback]() {
			if (players_manager::active_player_entity(entity_id)) {
				callback();
			}
		}));
	}
	template <typename Callback>
	void on_every_two_turns_from_next(Callback callback) {
		on_every_two_turns_from_next_holder = std::move(turn_system::set_callback(frequency_types::every_two_turns_from_next, 0, callback));
	}

private:
	turn_scoped_connection on_every_turn_holder;
	turn_scoped_connection on_every_two_turns_from_this_holder;
	turn_scoped_connection on_every_two_turns_from_next_holder;
	turn_scoped_connection after_player_turn_holder;
};

#endif