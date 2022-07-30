#include <get_game_state.h>

#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/game_controller.h>
#include <get_entity_names.h>

global_game_state get_global_game_state() {
  global_game_state state;
  state.healths = get_healths();
  state.board.resize(game_board().cols_n * game_board().rows_n);

  for (std::uint32_t i = 0; i < game_board().fields_.size(); ++i) {
    for (auto&& elem : game_board().fields_[i]) {
      state.board[i].push_back(elem);
    }
  }

  state.entities_names = get_entity_names();
  state.entities_players = get_entity_players();
  state.entities_additional_effects = get_effects();

  return state;
}

local_game_state get_local_game_state() {
  local_game_state local_state{};

  for (auto&& idx : game_control().possible_movements_)
    local_state.possible_movements.push_back(idx);

  local_state.actual_target_type = game_control().actual_targeting_type_;

  local_state.button_bitmaps.fill("");
  local_state.usable.fill(false);

  // verify this
  if (game_control().selected_index_ != no_selected_index) {
    auto entity_id = game_board().at(game_control().selected_index_);
    auto entity = game::get<entity_manager>().get(entity_id);

    if (entity_id != null_entity_id) {
      if (entity.contain<abilities>()) {
        auto abilities_ptr = entity.get<abilities>();
        for (std::int32_t i = 0; i < 5; ++i) {
          auto ability = abilities_ptr->at(i);
          if (ability) {
            local_state.button_bitmaps[i] = ability->get_name();
            local_state.usable[i] = ability->usable();
          }
        }
      }
    }

    local_state.entity_name = entity.name;
    local_state.selected_index = game_control().selected_index_;

    for (auto&& move : game_control().possible_movements_) {
      if (game_control().valid_target(move)) {
        local_state.valid_movements.insert(move);
      }
    }
  }

  return local_state;
}