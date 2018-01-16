#include "entity_manager.h"

std::unordered_map<std::uint64_t, base_entity> entity_manager::entities;

std::vector<std::function<void(std::uint64_t)>> entity_manager::on_destroy_callbacks;