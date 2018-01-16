#include <entities/tree.h>
#include "utils/creator_helper.h"
#include "core/board.h"
#include "managers/entity_manager.h"
#include "entities/stone.h"

namespace creator_helper
{
std::pair<std::uint64_t, std::uint64_t> pos(std::uint64_t col, std::uint64_t row)
{
	return std::make_pair(col, row);
}

void create_stones(std::vector<std::pair<std::uint64_t, std::uint64_t>>& positions)
{
	for (auto& position : positions)
	{
		std::uint64_t stone_id = entity_manager::create<stone>();
		board::insert(board::to_index(position.first, position.second), stone_id);
		players_manager::add_neutral_entity(stone_id);
	}
}

void create_stones(std::initializer_list<std::pair<std::uint64_t, std::uint64_t>> positions)
{
	for (auto& position : positions)
	{
		std::uint64_t stone_id = entity_manager::create<stone>();
		board::insert(board::to_index(position.first, position.second), stone_id);
		players_manager::add_neutral_entity(stone_id);
	}
}

void create_trees(std::initializer_list<std::pair<std::uint64_t, std::uint64_t>> positions)
{
	for (auto& position : positions)
	{
		std::uint64_t tree_id = entity_manager::create<tree>();
		board::insert(board::to_index(position.first, position.second), tree_id);
		players_manager::add_neutral_entity(tree_id);
	}
}
}