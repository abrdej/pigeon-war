#ifndef CREATOR_HELPER_H
#define CREATOR_HELPER_H

#include <vector>
#include <initializer_list>
#include "managers/entity_manager.h"

class board;
class entity_manager;
class players;
class stone;

namespace creator_helper
{

std::pair<std::size_t, std::size_t> pos(std::size_t col, std::size_t row);

void create_stones(std::vector<std::pair<std::size_t, std::size_t>>& positions);
void create_stones(std::initializer_list<std::pair<std::size_t, std::size_t>> positions);

template <typename T>
void create_neutral_many(std::vector<std::pair<std::size_t, std::size_t>>& positions) {
    for (auto& position : positions)
    {
        size_t id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players::add_neutral_entity(id);
    }
}

template <typename T>
void create_neutral_many(std::initializer_list<std::pair<std::size_t, std::size_t>> positions) {
    for (auto& position : positions)
    {
        size_t id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players::add_neutral_entity(id);
    }
}

void create_trees(std::initializer_list<std::pair<std::size_t, std::size_t>> positions);

}


#endif