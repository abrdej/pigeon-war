#include <abilities/smokescreen.h>

#include <components/applied_effects.h>
#include <core/board.h>

smokescreen::smokescreen(std::uint32_t entity_id) : path_target_ability(4), entity_id_(entity_id) {}

void smokescreen::use(std::uint32_t on_index) {
  if (used_) return;

  used_ = true;

  std::vector<std::uint32_t> neighbors;
  board_helper::neighboring_fields(on_index, neighbors, false);

  sender::send(make_action_message("smokescreen", game_control().selected_index_, on_index));

  auto enemy_id = game_board().at(on_index);
  set_smokescreen_effect(enemy_id);

  for (auto index : neighbors) {
    if (!game_board().empty(index) && players_helpers::is_enemy_entity(index)) {
      set_smokescreen_effect(game_board().at(index));
    }
  }
}

void smokescreen::set_smokescreen_effect(std::uint32_t enemy_id) {
  auto modification_ptr = game_get<entity_manager>().get(enemy_id).get<modification>();
  modification_ptr->modify_by(modifiers::shot_range, -range_reduction_);

  auto smokescreen_connection = make_after_n_round_callback_holder(
      duration_, [enemy_id, modification_ptr, range_reduction = range_reduction_]() mutable {
        modification_ptr->modify_by(modifiers::shot_range, range_reduction);
        remove_effect(enemy_id, "smokescreen");
      });

  auto web_effect = make_negative_effect("smokescreen");
  web_effect->set_turn_connection(std::move(smokescreen_connection));

  add_effect(enemy_id, web_effect);
}
