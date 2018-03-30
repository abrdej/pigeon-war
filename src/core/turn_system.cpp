#include <iostream>
#include "turn_system.h"

std::uint32_t turn_system::turn_n = 0;
std::unordered_multimap<std::uint32_t, std::function<void()>> turn_system::tasks;

turn_signal turn_system::next_turn_signal;

void turn_system::end_turn()
{
	++turn_n;

	next_turn_signal();

//	for (auto& callback_pack : callbacks) {
//
//		if (callback_pack.callback.exist()) {
//			const auto frequency = callback_pack.frequency;
//			if (frequency == frequency_types::every_turn) {
//				turn_callback_info info{callback_pack.duration && ++callback_pack.number_of_calls == callback_pack.duration,
//										callback_pack.callback};
//				callback_pack.callback(info);
//				if (info.ended) {
//					callback_pack.callback.destroy();
//				}
//
//			} else if (frequency == frequency_types::every_two_turns_from_this) {
//				turn_callback_info info{callback_pack.duration && ++callback_pack.number_of_calls == callback_pack.duration,
//										callback_pack.callback};
//				callback_pack.callback(info);
//				callback_pack.frequency = frequency_types::every_two_turns_from_next;
//				if (info.ended) {
//					callback_pack.callback.destroy();
//				}
//
//			} else if (frequency == frequency_types::every_two_turns_from_next) {
//				callback_pack.frequency = frequency_types::every_two_turns_from_this;
//
//			} else if (frequency == frequency_types::after_n_rounds) {
//				if (++callback_pack.number_of_calls == callback_pack.duration * 2) {
//					turn_callback_info info{true,
//											callback_pack.callback};
//					callback_pack.callback(info);
//					callback_pack.callback.destroy();
//				}
//			} else if (frequency == frequency_types::after_n_turns) {
//				if (++callback_pack.number_of_calls == callback_pack.duration) {
//					turn_callback_info info{true,
//											callback_pack.callback};
//					callback_pack.callback(info);
//					callback_pack.callback.destroy();
//				}
//			}
//		}
//	}

	auto result = tasks.equal_range(turn_n);
	auto it = result.first;
	for (; it != result.second; ++it)
	{
		it->second();
	}
}

void turn_system::on_turn(std::uint32_t turn_n, const std::function<void()>& task)
{
	tasks.insert(std::make_pair(turn_n, task));
}