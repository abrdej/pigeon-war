#include "entity_manager.h"

std::unordered_map<std::uint64_t, base_entity> entity_manager::entities;

std::unordered_map<std::uint64_t, std::vector<std::function<void()>>> entity_manager::on_destroy_callbacks;