#include <entities/tree.h>
#include "utils/creator_helper.h"
#include "core/board.h"
#include "managers/entity_manager.h"
#include "managers/players_manager.h"
#include "entities/stone.h"

namespace creator_helper
{
std::pair<std::uint32_t, std::uint32_t> pos(std::uint32_t col, std::uint32_t row)
{
	return std::make_pair(col, row);
}

void create_stones(std::vector<std::pair<std::uint32_t, std::uint32_t>>& positions)
{
	for (auto& position : positions)
	{
		std::uint32_t stone_id = game::get<entity_manager>().create<stone>();
		game::get<board>().insert(game::get<board>().to_index(position.first, position.second), stone_id);
		game::get<players_manager>().add_neutral_entity(stone_id);
	}
}

void create_stones(std::initializer_list<std::pair<std::uint32_t, std::uint32_t>> positions)
{
	for (auto& position : positions)
	{
		std::uint32_t stone_id = game::get<entity_manager>().create<stone>();
		game::get<board>().insert(game::get<board>().to_index(position.first, position.second), stone_id);
		game::get<players_manager>().add_neutral_entity(stone_id);
	}
}

void create_trees(std::initializer_list<std::pair<std::uint32_t, std::uint32_t>> positions)
{
	for (auto& position : positions)
	{
		std::uint32_t tree_id = game::get<entity_manager>().create<tree>();
		game::get<board>().insert(game::get<board>().to_index(position.first, position.second), tree_id);
		game::get<players_manager>().add_neutral_entity(tree_id);
	}
}
}