#include <managers/players_manager.h>

#include <core/board.h>

void players_helpers::player_entities_indexes(std::uint32_t player_id,
                                              std::vector<std::uint32_t> &indexes) {
  indexes.clear();
  game_board().for_each(
      [&player_id, &indexes](std::uint32_t entity_id, std::uint32_t col, std::uint32_t row) {
        if (entity_id != board::empty_id &&
            game::get<players_manager>().player_entity(player_id, entity_id))
          indexes.push_back(game_board().to_index(col, row));
      });
}

void players_helpers::enemy_entities_indexes(std::uint32_t player_id,
                                             std::vector<std::uint32_t> &indexes) {
  indexes.clear();
  game_board().for_each(
      [player_id, &indexes](std::uint32_t entity_id, std::uint32_t col, std::uint32_t row) {
        if (entity_id != board::empty_id &&
            game::get<players_manager>().enemy_entity(player_id, entity_id))
          indexes.push_back(game_board().to_index(col, row));
      });
}

bool players_helpers::is_player_entity(std::uint32_t entity_index) {
  auto entity_id = game_board().at(entity_index);
  if (entity_id != board::empty_id)
    return game::get<players_manager>().player_entity(
        game::get<players_manager>().get_active_player_id(), entity_id);
  return false;
}

bool players_helpers::is_enemy_entity(std::uint32_t entity_index) {
  auto entity_id = game_board().at(entity_index);
  if (entity_id != board::empty_id)
    return game::get<players_manager>().enemy_entity(
        game::get<players_manager>().get_active_player_id(), entity_id);
  return false;
}

bool players_helpers::is_neutral_entity(std::uint32_t entity_index) {
  auto entity_id = game_board().at(entity_index);
  return (entity_id != board::empty_id) ? game::get<players_manager>().neutral_entity(entity_id)
                                        : false;
}

std::uint32_t players_helpers::active_player_first_entity_index() {
  std::vector<std::uint32_t> indexes;
  player_entities_indexes(game::get<players_manager>().get_active_player_id(), indexes);
  return !indexes.empty() ? indexes[0] : no_selected_index;
}
