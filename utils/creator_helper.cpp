#include <entities/tree.h>
#include "utils/creator_helper.h"
#include "core/board.h"
#include "managers/entity_manager.h"
#include "core/players.h"
#include "entities/stone.h"

namespace creator_helper
{
std::pair<size_t, size_t> pos(size_t col, size_t row)
{
	return std::make_pair(col, row);
}

void create_stones(std::vector<std::pair<size_t, size_t>>& positions)
{
	for (auto& position : positions)
	{
		size_t stone_id = entity_manager::create(stone::create());
		board::insert(board::to_index(position.first, position.second), stone_id);
		players::add_neutral_entity(stone_id);
	}
}

void create_stones(std::initializer_list<std::pair<size_t, size_t>> positions)
{
	for (auto& position : positions)
	{
		size_t stone_id = entity_manager::create(stone::create());
		board::insert(board::to_index(position.first, position.second), stone_id);
		players::add_neutral_entity(stone_id);
	}
}

void create_trees(std::initializer_list<std::pair<size_t, size_t>> positions)
{
	for (auto& position : positions)
	{
		size_t tree_id = entity_manager::create(tree::create());
		board::insert(board::to_index(position.first, position.second), tree_id);
		players::add_neutral_entity(tree_id);
	}
}
}