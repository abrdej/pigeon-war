#include <poisoned_missile.h>

#include <turn_based/abilities.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/move.h>
#include <turn_based/board.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>
#include <turn_based/components/applied_effects.h>

poisoned_missile::poisoned_missile(entity_id_t entity_id)
    : path_target_ability(name, 4), entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)),
      poison_power_(get_param_or_default("poison_power", poison_power_)),
      poison_duration_(get_param_or_default("poison_duration", poison_duration_)) {
  configure_hint(config_directory + name + ".json", "hint", damage_, poison_duration_, poison_power_);

  LOG(debug) << "Poisoned missile setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
  LOG(debug) << "poison_power: " << poison_power_;
  LOG(debug) << "poison_duration: " << poison_duration_;
}

void poisoned_missile::use(index_t index_on) {
  if (used) {
    return;
  }

  auto from_index = game_control().selected_index;

  sender::send(make_action_message("poisoned_missile", from_index, index_on));

  auto entity_id = game_board().at(from_index);
  auto enemy_id = game_board().at(index_on);

  damage_dealers::standard_damage_dealer(ranged_damage(damage_, enemy_id, entity_id));

  if (game::get<entity_manager>().alive(enemy_id)) {
    auto poison_power = poison_power_;
    auto poison_duration = poison_duration_;
    auto poisoned_connection = make_every_two_turns_from_next_callback_holder(
        poison_duration, [enemy_id, poison_power](const turn_callback_info& info) mutable {
          sender::send(make_action_message("poison", game_board().index_for(enemy_id)));
          damage_dealers::standard_damage_dealer(special_damage(poison_power, enemy_id));
          if (info.is_ending) {
            if (game::get<entity_manager>().alive(enemy_id)) {
              remove_effect(enemy_id, "poisoning");
            }
          }
        });

    auto poison_effect = make_negative_effect("poisoning");
    poison_effect->set_turn_connection(std::move(poisoned_connection));
    add_effect(enemy_id, poison_effect);
  }

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto move_ptr =
      std::dynamic_pointer_cast<move_ability>(abilities_ptr->of_type(ability_types::moving));
  if (move_ptr) {
    move_ptr->refresh_range();
  }

  used = true;
}
