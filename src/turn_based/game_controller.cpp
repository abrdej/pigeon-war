#include <turn_based/game_controller.h>

#include <turn_based/abilities.h>
#include <turn_based/ai/ai_manager.h>
#include <turn_based/board.h>
#include <turn_based/game.h>
#include <turn_based/states.h>
#include <turn_based/turn_system.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>
#include <turn_based/utils/algorithm.h>

void game_controller::set_entity_default_state(index_t select_from_index) {
  if (select_from_index == no_selected_index) return;

  selected_index_ = select_from_index;
  index_t selected_index = selected_index_;

  auto entity_id = game_board().at(selected_index);
  auto entity = game::get<entity_manager>().get(entity_id);

  if (entity.contain<abilities>()) {
    auto abilities_ptr = entity.get<abilities>();

    if (abilities_ptr->is_active) {
      auto moveable = abilities_ptr->at(0);
      if (moveable) {
        try_prepare_ability(*moveable, selected_index_);
      }
    }
  }
}

void game_controller::on_board(std::uint32_t col, std::uint32_t row) {
  auto index = game_board().to_index(col, row);

  if (game_board().empty(index) && actual_state_ == states_types::waiting)
    return;

  else if (actual_state_ == states_types::wait_for_action) {
    if (is_possible_movement(index) && valid_target(index)) {
      do_action(index);
    } else if (!game_board().empty(index) && players_helpers::is_player_entity(index))
      set_entity_default_state(index);

    else if (!game_board().empty(index) && !players_helpers::is_player_entity(index)) {
      actual_state_ = states_types::waiting;
      actual_targeting_type_ = target_types::non;
      selected_index_ = index;
    }
  } else if (!game_board().empty(index) && players_helpers::is_player_entity(index)) {
    set_entity_default_state(index);
  } else if (!game_board().empty(index) && !players_helpers::is_player_entity(index)) {
    actual_state_ = states_types::waiting;
    actual_targeting_type_ = target_types::non;
    selected_index_ = index;
  }
}

void game_controller::on_button(std::uint32_t n) {
  if (n >= 0 && n <= 3)  // 4 is passive
  {
    auto selected_index = game_control().selected_index_;

    if (!players_helpers::is_player_entity(selected_index)) {
      LOG(debug) << "not player entity";
      return;
    }

    auto entity_id = game_board().at(selected_index);
    auto entity = game::get<entity_manager>().get(entity_id);

    if (entity.contain<abilities>()) {
      auto abilities_ptr = entity.get<abilities>();

      if (abilities_ptr->is_active) {
        auto entity_ability = abilities_ptr->at(n);
        if (entity_ability) {
          try_prepare_ability(*entity_ability, selected_index_);
        }
      }
    }
  }
  if (n == 5) {
    game::get<turn_system>().end_turn();
    game::get<players_manager>().next_player();
    set_entity_default_state(players_helpers::active_player_first_entity_index());

    if (game::get<players_manager>().is_active_player_ai()) {
      //            game::get<ai_manager>().perform_movement(game::get<players_manager>().get_active_player_id());
      game::get<ai_manager>().perform_movement_new_ai(game::get<players_manager>().get_active_player_id());
      game::get<turn_system>().end_turn();
      game::get<players_manager>().next_player();
      set_entity_default_state(players_helpers::active_player_first_entity_index());
    }
  }
}

void game_controller::defeat() {
  sender::send(make_defeat_message());
}

void game_controller::victory(std::uint32_t player_id) {
  sender::send(make_victory_message());
}

void game_controller::wait_for_action(const std::function<void(std::uint32_t index)>& caller) {
  actual_state_ = states_types::wait_for_action;
  action_ = caller;
}

void game_controller::do_action(index_t index) { action_(index); }

bool game_controller::is_possible_movement(index_t index) {
  return has_value(possible_movements_, index);
}

bool game_controller::valid_target(index_t target_index) {
  switch (actual_targeting_type_) {
    case target_types::enemy: {
      auto caster_id = game_board().at(selected_index_);

      std::uint32_t target_value = target_index;

      if (custom_valid_target_type == custom_target_type::entity_id)
        target_value = game_board().at(target_index);

      if (!custom_valid_targets[caster_id].empty()) {
        LOG(debug) << "custom";

        return custom_valid_targets[caster_id].find(target_value) != std::end(custom_valid_targets[caster_id]);
      }

      return players_helpers::is_enemy_entity(target_index);
    }
    case target_types::moving:return game_board().empty(target_index);
    case target_types::friendly:return players_helpers::is_player_entity(target_index);
    case target_types::caster:return target_index == selected_index_;
    case target_types::neutral:return players_helpers::is_neutral_entity(target_index);
    case target_types::all:return true;
    default:return false;
  }
}