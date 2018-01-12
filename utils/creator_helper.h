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

std::pair<sf::Uint64, sf::Uint64> pos(sf::Uint64 col, sf::Uint64 row);

void create_stones(std::vector<std::pair<sf::Uint64, sf::Uint64>>& positions);
void create_stones(std::initializer_list<std::pair<sf::Uint64, sf::Uint64>> positions);

template <typename T>
void create_neutral_many(std::vector<std::pair<sf::Uint64, sf::Uint64>>& positions) {
    for (auto& position : positions)
    {
        sf::Uint64 id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players_manager::add_neutral_entity(id);
    }
}

template <typename T>
void create_neutral_many(std::initializer_list<std::pair<sf::Uint64, sf::Uint64>> positions) {
    for (auto& position : positions)
    {
        sf::Uint64 id = entity_manager::create<T>();
        board::insert(board::to_index(position.first, position.second), id);
        players_manager::add_neutral_entity(id);
    }
}

void create_trees(std::initializer_list<std::pair<sf::Uint64, sf::Uint64>> positions);

}


#endif