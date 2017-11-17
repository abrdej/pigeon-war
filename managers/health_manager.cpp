#include "health_manager.h"

std::unordered_map<size_t, std::vector<std::function<void()>>> healths_manager::on_receive_damage_callbacks;

std::unordered_map<size_t, healths_manager::damage_receiver> healths_manager::damage_receivers;