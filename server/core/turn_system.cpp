#include <iostream>
#include "turn_system.h"

namespace turn
{
std::uint64_t turn_system::turn_n_ = 0;
std::unordered_multimap<std::uint64_t, std::function<void()>> turn_system::tasks_;

turn_system::signal_type turn_system::every_round_signal_;
turn_system::signal_type turn_system::every_turn_signal_;

void turn_system::end_turn()
{
	++turn_n_;

	every_turn_signal_.send_event();

	if (turn_n_ % 2)
		every_round_signal_.send_event();

	auto result = tasks_.equal_range(turn_n_);
	auto it = result.first;
	for (; it != result.second; ++it)
	{
		it->second();
	}
}

void turn_system::on_turn(std::uint64_t turn_n, const std::function<void()>& task)
{
	tasks_.insert(std::make_pair(turn_n, task));
}

turn_system::strong_receiver turn_system::every_round(std::function<void()> callback)
{
	return every_round_signal_.add_receiver(std::make_shared<std::function<void()>>(callback));
}

turn_system::strong_receiver turn_system::every_turn(std::function<void()> callback)
{
	return every_turn_signal_.add_receiver(std::make_shared<std::function<void()>>(callback));
}

};