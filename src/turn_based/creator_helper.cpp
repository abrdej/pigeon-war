#include <turn_based/creator_helper.h>

#include <turn_based/board.h>
#include <turn_based/entities_factory.h>
#include <turn_based/game.h>
#include <turn_based/managers/players_manager.h>

namespace creator_helper {

pos_type pos(std::uint32_t col, std::uint32_t row) {
  return std::make_pair(col, row);
}

void create_neutral_many(const std::string& entity_name,
                         const std::vector<pos_type>& positions) {
  for (const auto& position : positions) {
    std::uint32_t entity_id = game::get<entities_factory>().create(entity_name);
    game_board().insert(game_board().to_index(position.first, position.second), entity_id);
    game::get<players_manager>().add_neutral_entity(entity_id);
  }
}

void create_around_map(const std::string& name) {
  std::vector<std::pair<std::uint32_t, std::uint32_t>> positions;
  for (std::int32_t i = 0; i < game_board().cols_n; ++i) {
    for (std::int32_t j = 0; j < game_board().rows_n; ++j) {
      if (i == 0 || j == 0 || i == game_board().cols_n - 1 || j == game_board().rows_n - 1) {
        positions.push_back(pos(i, j));
      }
    }
  }
  create_neutral_many(name, positions);
}

}  // namespace creator_helper
