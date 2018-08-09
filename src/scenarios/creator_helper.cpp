#include "creator_helper.h"

#include <entities/entities_factory.h>

std::pair<std::uint32_t, std::uint32_t> creator_helper::pos(std::uint32_t col, std::uint32_t row)
{
	return std::make_pair(col, row);
}

void creator_helper::create_neutral_many(const std::string& entity_name,
                                         const std::vector<std::pair<std::uint32_t, std::uint32_t>>& positions) {
    for (const auto& position : positions) {
        std::uint32_t entity_id = entities_factory::create(entity_name);
        game_board().insert(game_board().to_index(position.first, position.second), entity_id);
        game::get<players_manager>().add_neutral_entity(entity_id);
    }
}
