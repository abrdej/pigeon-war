#ifndef TURN_H
#define TURN_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include "managers/players_manager.h"
#include "signals.h"

namespace turn
{

// turn_system is responsible to send events releted to turns
// there are some kinds of event
//

class turn_system
{
public:
	using signal_type = signal;
	using strong_receiver = signal_type::strong_receiver;
	using weak_receiver = signal_type::weak_receiver;
	using callback = signal_type::callback;

	static void end_turn();
	static void on_turn(sf::Uint64 turn_n, const std::function<void()>& task);
	static strong_receiver every_round(std::function<void()> callback);
	static strong_receiver every_turn(std::function<void()> callback);

private:
	static sf::Uint64 turn_n_;
	static std::unordered_multimap<sf::Uint64, std::function<void()>> tasks_;
	static signal_type every_round_signal_;
	static signal_type every_turn_signal_;
};
};

namespace turn_events_helper
{

class every_turn_callback_helper
{
protected:
	using callback_type = turn::turn_system::callback;

	template <typename Callback>
	void onEveryRound(Callback callback)
	{
		end_round_receiver_ = turn::turn_system::every_round(callback);
	}
	template <typename Callback>
	void onEveryTurn(Callback callback)
	{
		end_turn_receiver_ = turn::turn_system::every_turn(callback);
	}
	template <typename Callback>
	void onTwoTurns(Callback callback)
	{
		every_turns_receiver_ = turn::turn_system::every_turn([this, callback]() {

			std::cout << state << "\n";

			if (state) {
				callback();
			}
			state = !state;
		});
	}
private:
	bool state{false};
	turn::turn_system::strong_receiver end_round_receiver_;
	turn::turn_system::strong_receiver end_turn_receiver_;
	turn::turn_system::strong_receiver every_turns_receiver_;
};

struct on_every_round : every_turn_callback_helper {
	template <typename Callback>
	explicit on_every_round(Callback callback) {
		onEveryRound(callback);
	}
};

}

#endif