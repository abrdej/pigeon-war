#include <entities/tree.h>
#include "utils/creator_helper.h"
#include "core/board.h"
#include "managers/entity_manager.h"
#include "entities/stone.h"

namespace creator_helper
{
std::pair<sf::Uint64, sf::Uint64> pos(sf::Uint64 col, sf::Uint64 row)
{
	return std::make_pair(col, row);
}

void create_stones(std::vector<std::pair<sf::Uint64, sf::Uint64>>& positions)
{
	for (auto& position : positions)
	{
		sf::Uint64 stone_id = entity_manager::create<stone>();
		board::insert(board::to_index(position.first, position.second), stone_id);
		players_manager::add_neutral_entity(stone_id);
	}
}

void create_stones(std::initializer_list<std::pair<sf::Uint64, sf::Uint64>> positions)
{
	for (auto& position : positions)
	{
		sf::Uint64 stone_id = entity_manager::create<stone>();
		board::insert(board::to_index(position.first, position.second), stone_id);
		players_manager::add_neutral_entity(stone_id);
	}
}

void create_trees(std::initializer_list<std::pair<sf::Uint64, sf::Uint64>> positions)
{
	for (auto& position : positions)
	{
		sf::Uint64 tree_id = entity_manager::create<tree>();
		board::insert(board::to_index(position.first, position.second), tree_id);
		players_manager::add_neutral_entity(tree_id);
	}
}
}