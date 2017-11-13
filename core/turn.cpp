#include "turn.h"
#include "event_center.h"

namespace turn
{
	size_t turn_system::turn_n_ = 0;
	std::unordered_multimap<size_t, std::function<void()>> turn_system::tasks_;
	
	turn_system::every_turn_signal_type turn_system::every_turn_signal_;

	void turn_system::end_turn()
	{
		++turn_n_;
		if (turn_n_ % 2)
			every_turn_signal_.send_event();

		auto result = tasks_.equal_range(turn_n_);
		auto it = result.first;
		for (; it != result.second; ++it)
		{
			it->second();
		}
	}

	void turn_system::on_turn(size_t turn_n, const std::function<void()>& task)
	{
		tasks_.insert(std::make_pair(turn_n, task));
	}

	turn_system::every_turn_signal_type::strong_receiver
		turn_system::every_turn(const every_turn_signal_type::strong_receiver& task)
	{
		return every_turn_signal_.add_receiver(task);
	}
};