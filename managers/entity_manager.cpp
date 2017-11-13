#include "entity_manager.h"

std::unordered_set<size_t> entity_manager::entities_;
size_t entity_manager::next_ = 0;
std::vector<std::function<void(size_t)>> entity_manager::on_destroy_callbacks_;