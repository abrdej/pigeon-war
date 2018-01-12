#include "entity_manager.h"

std::unordered_set<sf::Uint64> entity_manager::entities_;

std::vector<std::function<void(sf::Uint64)>> entity_manager::on_destroy_callbacks_;