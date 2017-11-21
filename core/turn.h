#ifndef TURN_H
#define TURN_H

#include <vector>
#include <string>
#include <unordered_map>
#include "players.h"
#include "core/signals.h"

namespace turn
{
class turn_system
{
public:
	using every_turn_signal_type = signal<>;

	static void end_turn();
	static void on_turn(size_t turn_n, const std::function<void()>& task);
	static every_turn_signal_type::strong_receiver every_round(std::function<void()> callback);
	static every_turn_signal_type::strong_receiver every_turn(std::function<void()> callback);
private:
	static size_t turn_n_;
	static std::unordered_multimap<size_t, std::function<void()>> tasks_;
	static every_turn_signal_type every_round_signal_;
	static every_turn_signal_type every_turn_signal_;
};
};

namespace turn_events_helper
{

class every_turn_callback_helper
{
protected:
	using callback_type = turn::turn_system::every_turn_signal_type::callback;

	template <typename Callback>
	void onEveryTurn(Callback callback)
	{
		end_turn_receiver_ = turn::turn_system::every_round(callback);
	}
private:
	turn::turn_system::every_turn_signal_type::strong_receiver end_turn_receiver_;
};

struct on_every_turn : every_turn_callback_helper {
	template <typename Callback>
	explicit on_every_turn(Callback callback) {
		onEveryTurn(callback);
	}
};

}

#endif