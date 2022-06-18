#include <turn_based/abilities.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/moveable.h>
#include <poisoned_missile.h>
#include <components/applied_effects.h>
#include <turn_based/board.h>
#include <turn_based/game_controller.h>
#include <effects/poison_effect.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

poisoned_missile::poisoned_missile(std::uint32_t entity_id)
  : path_target_ability(entity_id, 4) {}

void poisoned_missile::use(std::uint32_t index_on) {
  if (used) return;

  auto from_index = game_control().selected_index_;

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

  auto moveable_ptr =
      std::dynamic_pointer_cast<moveable_base>(abilities_ptr->of_type(ability_types::moving));
  if (moveable_ptr) {
    moveable_ptr->refresh_range();
  }

  used = true;
}

std::string poisoned_missile::hint() const {
  std::string desc;
  desc = "Poisoned Missile - deals damage of " + std::to_string(damage_) +
         "\n"
         " and poisons the opponent for " +
         std::to_string(poison_duration_) +
         " turn."
         "Poison deals " +
         std::to_string(poison_power_) + " damage per turn.";

  return std::move(desc);
}