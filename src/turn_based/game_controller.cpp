#include <turn_based/game_controller.h>

#include <turn_based/abilities.h>
#include <turn_based/ai/ai_manager.h>
#include <turn_based/board.h>
#include <turn_based/game.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>
#include <turn_based/states.h>
#include <turn_based/turn_system.h>
#include <turn_based/utils/algorithm.h>

void game_controller::on_board(std::uint32_t col, std::uint32_t row) {
  auto index = game_board().to_index(col, row);

  if (game_board().empty(index) && current_state == states_types::waiting) {
    return;

  } else if (current_state == states_types::wait_for_action) {
    if (is_possible_movement(index) && valid_target(index)) {
      do_action(index);

    } else if (!game_board().empty(index) && players_helpers::is_player_entity(index))
      set_entity_default_state(index);

    else if (!game_board().empty(index) && !players_helpers::is_player_entity(index)) {
      current_state = states_types::waiting;
      current_targeting_type = target_types::non;
      selected_index = index;
    }

  } else if (!game_board().empty(index) && players_helpers::is_player_entity(index)) {
    set_entity_default_state(index);

  } else if (!game_board().empty(index) && !players_helpers::is_player_entity(index)) {
    current_state = states_types::waiting;
    current_targeting_type = target_types::non;
    selected_index = index;
  }
}

void game_controller::on_button(std::uint32_t n) {
  if (n <= 4) {
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
          try_prepare_ability(*entity_ability, selected_index);
        }
      }
    }

  } else if (n == 5) {
    game::get<turn_system>().end_turn();
    game::get<players_manager>().next_player();
    set_entity_default_state(players_helpers::active_player_first_entity_index());

    if (game::get<players_manager>().is_active_player_ai()) {
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

void game_controller::victory(player_id_t player_id) {
  sender::send(make_victory_message());
}

void game_controller::wait_for_action(const std::function<void(index_t index)>& caller) {
  current_state = states_types::wait_for_action;
  action_ = caller;
}

void game_controller::do_action(index_t index) { action_(index); }

bool game_controller::is_possible_movement(index_t index) const {
  return has_value(possible_movements, index);
}

bool game_controller::valid_target(index_t target_index) {
  auto caster_id = game_board().at(selected_index);

  // TODO: verify this
  // Allow to set custom valid target independently of ability type.
  if (custom_target_indices_[caster_id].empty()) {
    auto is_custom_valid_index = custom_target_indices_[caster_id].count(target_index) > 0;
    if (is_custom_valid_index) {
      return true;
    }
  }

  if (custom_target_entities_[caster_id].empty()) {
    auto is_custom_valid_entity = custom_target_entities_[caster_id].count(game_board().at(target_index)) > 0;
    if (is_custom_valid_entity) {
      return true;
    }
  }

  switch (current_targeting_type) {
    case target_types::enemy: return players_helpers::is_enemy_entity(target_index);
    case target_types::moving: return game_board().empty(target_index);
    case target_types::friendly: return players_helpers::is_player_entity(target_index);
    case target_types::caster: return target_index == selected_index;
    case target_types::neutral: return players_helpers::is_neutral_entity(target_index);
    case target_types::all: return true;
    default: return false;
  }
}

void game_controller::add_custom_valid_target_entities(
    entity_id_t entity_id, const std::vector<entity_id_t>& custom_target_entities) {
  for (auto custom_target : custom_target_entities) {
    custom_target_entities_[entity_id].insert(custom_target);
  }
}

void game_controller::add_custom_valid_target_indices(
    entity_id_t entity_id, const std::vector<index_t>& custom_target_indices) {
  for (auto custom_target : custom_target_indices) {
    custom_target_indices_[entity_id].insert(custom_target);
  }
}

void game_controller::reset_custom_valid_targets_entities(entity_id_t entity_id) {
  custom_target_entities_[entity_id].clear();
}

void game_controller::reset_custom_valid_targets_indices(entity_id_t entity_id) {
  custom_target_indices_[entity_id].clear();
}

void game_controller::set_entity_default_state(index_t select_from_index) {
  if (select_from_index == null_index) {
    return;
  }

  selected_index = select_from_index;

  auto entity_id = game_board().at(selected_index);
  auto entity = game::get<entity_manager>().get(entity_id);

  if (entity.contain<abilities>()) {
    auto abilities_ptr = entity.get<abilities>();
    if (abilities_ptr->is_active) {
      auto default_ability = abilities_ptr->at(0);
      if (default_ability) {
        try_prepare_ability(*default_ability, selected_index);
      }
    }
  }
}
