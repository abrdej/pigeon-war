#include "entity_manager.h"

std::unordered_set<size_t> entity_manager::entities_;

std::vector<std::function<void(size_t)>> entity_manager::on_destroy_callbacks_;