#include <iostream>
#include "turn_system.h"

std::uint32_t turn_system::turn_n = 0;
std::unordered_multimap<std::uint32_t, std::function<void()>> turn_system::tasks;

std::unordered_map<std::uint32_t, turn_system::callback_pack> turn_system::callbacks;

std::unordered_set<std::uint32_t> turn_system::callbacks_to_remove;
std::vector<std::pair<std::uint32_t, turn_system::callback_pack>> turn_system::callbacks_to_set;

void turn_system::end_turn()
{
	++turn_n;

	for (auto&& callback_id : callbacks_to_remove) {
		callbacks.erase(callback_id);
	}

	callbacks_to_remove.clear();

	for (auto&& callback_pack : callbacks_to_set) {
		callbacks.emplace(callback_pack.first, callback_pack.second);
	}

	callbacks_to_set.clear();

	for (auto& callback_pack : callbacks) {

		if (callbacks_to_remove.find(callback_pack.first) == std::end(callbacks_to_remove)) {
			const auto frequency = callback_pack.second.frequency;
			if (frequency == frequency_types::every_turn) {
				turn_callback_info info{callback_pack.second.duration && ++callback_pack.second.number_of_calls == callback_pack.second.duration,
										callback_pack.first};
				callback_pack.second.callback(info);
				if (info.ended) {
					callbacks_to_remove.insert(callback_pack.first);
				}

			} else if (frequency == frequency_types::every_two_turns_from_this) {
				turn_callback_info info{callback_pack.second.duration && ++callback_pack.second.number_of_calls == callback_pack.second.duration,
										callback_pack.first};
				callback_pack.second.callback(info);
				callback_pack.second.frequency = frequency_types::every_two_turns_from_next;
				if (info.ended) {
					callbacks_to_remove.insert(callback_pack.first);
				}

			} else if (frequency == frequency_types::every_two_turns_from_next) {
				callback_pack.second.frequency = frequency_types::every_two_turns_from_this;

			} else if (frequency == frequency_types::after_n_rounds) {
				if (++callback_pack.second.number_of_calls == callback_pack.second.duration * 2) {
					turn_callback_info info{true,
											callback_pack.first};
					callback_pack.second.callback(info);
					callbacks_to_remove.insert(callback_pack.first);
				}
			} else if (frequency == frequency_types::after_n_turns) {
				if (++callback_pack.second.number_of_calls == callback_pack.second.duration) {
					turn_callback_info info{true,
											callback_pack.first};
					callback_pack.second.callback(info);
					callbacks_to_remove.insert(callback_pack.first);
				}
			}
		}
	}

	for (auto&& callback_id : callbacks_to_remove) {
		callbacks.erase(callback_id);
	}

	callbacks_to_remove.clear();

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