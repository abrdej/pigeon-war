#pragma once

#include <initializer_list>
#include <vector>

#include <core/board.h>
#include <core/game.h>

#include <managers/entity_manager.h>
#include <managers/players_manager.h>

namespace creator_helper {

using pos_type = std::pair<std::uint32_t, std::uint32_t>;

pos_type pos(std::uint32_t col, std::uint32_t row);

template <typename T>
inline void create_neutral_many(const std::vector<pos_type>& positions) {
  for (const auto& position : positions) {
    std::uint32_t entity_id = game::get<entity_manager>().create<T>();
    game_board().insert(game_board().to_index(position.first, position.second), entity_id);
    game::get<players_manager>().add_neutral_entity(entity_id);
  }
}

template <typename T>
inline void create_neutral_many(std::initializer_list<pos_type> positions) {
  create_neutral_many<T>(std::vector<pos_type>(positions));
}

void create_neutral_many(const std::string& entity_name, const std::vector<pos_type>& positions);

}  // namespace creator_helper
