#include "health_manager.h"

//std::unordered_map<size_t,
//		std::vector<std::pair<healths_manager::on_receive_damage_policy,
//		std::function<void(const damage_pack&)>>>> healths_manager::on_receive_damage_callbacks;

std::unordered_map<size_t, healths_manager::damage_receiver> healths_manager::damage_receivers;

std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_before_callbacks;

std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_after_callbacks;