#ifndef CREATOR_HELPER_H
#define CREATOR_HELPER_H

#include <vector>
#include <initializer_list>
#include <entities/entities_factory.h>
#include "managers/entity_manager.h"
#include "managers/players_manager.h"

class board;
class entity_manager;
class players;
class stone;

namespace creator_helper
{

std::pair<std::uint32_t, std::uint32_t> pos(std::uint32_t col, std::uint32_t row);

void create_stones(std::vector<std::pair<std::uint32_t, std::uint32_t>>& positions);
void create_stones(std::initializer_list<std::pair<std::uint32_t, std::uint32_t>> positions);

template <typename T>
void create_neutral_many(std::vector<std::pair<std::uint32_t, std::uint32_t>>& positions) {
    for (auto& position : positions)
    {
        std::uint32_t id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players_manager::add_neutral_entity(id);
    }
}

template <typename T>
void create_neutral_many(std::initializer_list<std::pair<std::uint32_t, std::uint32_t>> positions) {
    for (auto& position : positions)
    {
        std::uint32_t id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players_manager::add_neutral_entity(id);
    }
}

inline void create_neutral_many(const std::string& entity_name, const std::vector<std::pair<std::uint32_t, std::uint32_t>>& positions) {
    for (auto& position : positions)
    {
        std::uint32_t id = entities_factory::create(entity_name);
        board::insert(board::to_index(position.first, position.second), id);
        players_manager::add_neutral_entity(id);
    }
}

void create_trees(std::initializer_list<std::pair<std::uint32_t, std::uint32_t>> positions);

}


#endif