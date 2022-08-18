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

  if (game_board().empty(index) && actual_state_ == states_types::waiting) {
    return;

  } else if (actual_state_ == states_types::wait_for_action) {
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
  if (n <= 4) {
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

void game_controller::victory(std::uint32_t player_id) {
  sender::send(make_victory_message());
}

void game_controller::wait_for_action(const std::function<void(index_t index)>& caller) {
  actual_state_ = states_types::wait_for_action;
  action_ = caller;
}

void game_controller::do_action(index_t index) { action_(index); }

bool game_controller::is_possible_movement(index_t index) const {
  return has_value(possible_movements_, index);
}

bool game_controller::valid_target(index_t target_index) {
  auto caster_id = game_board().at(selected_index_);

  // TODO: verify this
  // Allow to set custom valid target independently of ability type.
  if (custom_indices_targets_[caster_id].empty()) {
    auto is_custom_valid_index = custom_indices_targets_[caster_id].count(target_index) > 0;
    if (is_custom_valid_index) {
      return true;
    }
  }

  if (custom_entities_targets_[caster_id].empty()) {
    auto is_custom_valid_entity = custom_entities_targets_[caster_id].count(game_board().at(target_index)) > 0;
    if (is_custom_valid_entity) {
      return true;
    }
  }

  switch (actual_targeting_type_) {
    case target_types::enemy: return players_helpers::is_enemy_entity(target_index);
    case target_types::moving: return game_board().empty(target_index);
    case target_types::friendly: return players_helpers::is_player_entity(target_index);
    case target_types::caster: return target_index == selected_index_;
    case target_types::neutral: return players_helpers::is_neutral_entity(target_index);
    case target_types::all: return true;
    default: return false;
  }
}

void game_controller::set_custom_valid_targets(entity_id_t entity_id, const std::vector<entity_id_t>& custom_entities_targets) {
  for (auto custom_target : custom_entities_targets) {
    custom_entities_targets_[entity_id].insert(custom_target);
  }
}

void game_controller::set_custom_valid_targets(entity_id_t entity_id, const std::vector<index_t>& custom_indices_targets) {
  for (auto custom_target : custom_indices_targets) {
    custom_indices_targets_[entity_id].insert(custom_target);
  }
}

void game_controller::set_entity_default_state(index_t select_from_index) {
  if (select_from_index == null_index) {
    return;
  }

  selected_index_ = select_from_index;
  index_t selected_index = selected_index_;

  auto entity_id = game_board().at(selected_index);
  auto entity = game::get<entity_manager>().get(entity_id);

  if (entity.contain<abilities>()) {
    auto abilities_ptr = entity.get<abilities>();
    if (abilities_ptr->is_active) {
      auto default_ability = abilities_ptr->at(0);
      if (default_ability) {
        try_prepare_ability(*default_ability, selected_index_);
      }
    }
  }
}
