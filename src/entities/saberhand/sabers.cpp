#include <sabers.h>

#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/board_helpers.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/utils/algorithm.h>

sabers::sabers(entity_id_t entity_id)
    : active_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {

  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Sabers setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void sabers::prepare(index_t for_index) {
  game_control().selected_index_ = for_index;
  board_helper::neighboring_fields(for_index, game_control().possible_movements_, false);
  game_control().actual_targeting_type_ = target_types::enemy;
  game_control().wait_for_action([this](index_t index) {
    return target(index);
  });
}

void sabers::target(index_t target_index) {
  if (has_value(targets_, target_index)) {
    if (used) {
      return;
    }

    used = true;

    // fetch targets as we may become dead
    auto targets = std::move(targets_);
    for (auto targeted_index : targets) {
      use(targeted_index);
    }
    use(target_index);

  } else {
    targets_.push_back(target_index);

    board_helper::neighboring_fields(target_index, game_control().possible_movements_, false);
    game_control().possible_movements_.push_back(target_index);
    game_control().actual_targeting_type_ = target_types::enemy;
    game_control().wait_for_action([this](index_t index) {
      return target(index);
    });
  }
}

void sabers::use(index_t index_on) {
  if (game_board().empty(index_on)) {
    return;
  }

  if (!game_get<entity_manager>().alive(entity_id_)) {
    return;
  }

  sender::send(make_action_message(name, entity_id_, index_on));

  damage_dealers::standard_damage_dealer(melee_damage(damage_, game_board().at(index_on), entity_id_));

  game_control().selected_index_ = game_board().index_for(entity_id_);
  game_control().possible_movements_.clear();
}
