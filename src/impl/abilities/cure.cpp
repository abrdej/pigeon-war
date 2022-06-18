#include <cure.h>

#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/power_field.h>
#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

#include <turn_based/damage_dealers.h>
#include <power_cost_ability.h>

cure::cure(std::uint32_t entity_id)
    : path_target_ability(3, target_types::friendly), entity_id_(entity_id) {}

bool cure::usable() const {
  auto& power = game::get<entity_manager>().get(entity_id_).get<power_filed>()->power;
  return power >= power_cost_;
}

void cure::use(std::uint32_t index_on) {
  if (used) {
    return;
  }

  auto& power = game::get<entity_manager>().get(entity_id_).get<power_filed>()->power;
  if (power < power_cost_) {
    return;
  }

  auto friend_id = game_board().at(index_on);

  sender::send(make_action_message("cure", index_on));

  standard_healing(healing_to_base_health(healing_amount_per_turn_, friend_id));

  auto healing_amount_per_turn = healing_amount_per_turn_;
  auto healing_duration = healing_duration_;

  auto cure_connection = make_every_two_turns_from_next_callback_holder(
      healing_duration, [healing_amount_per_turn, friend_id]() {
        if (game::get<entity_manager>().alive(friend_id)) {
          sender::send(make_action_message("cure", game_board().index_for(friend_id)));
          standard_healing(healing_to_base_health(healing_amount_per_turn, friend_id));
        }
      });

  auto cure_effect = make_positive_effect("cure");
  cure_effect->set_turn_connection(std::move(cure_connection));

  add_effect(friend_id, cure_effect);

  power -= power_cost_;
  sender::send(make_action_message("change_power", entity_id_, -power_cost_));

  used = true;
}