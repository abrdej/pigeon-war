#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include <effects/poison_effect.h>
#include <abilities/abilities.h>
#include <messages/make_message.h>
#include "components/applied_effects.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"
#include "abilities/moveable.h"
#include "sender.h"

void poisoned_missile::use(std::uint32_t index_on) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;

    sender::send(make_action_message("poisoned_missile", from_index, index_on));

    auto entity_id = board::at(from_index);
    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, enemy_id, entity_id));

    if (entity_manager::alive(enemy_id)) {

        auto poison_power = this->poison_power;
        auto poison_duration = this->poison_duration;

        auto poisoned_connection = make_every_two_turns_from_next_callback_holder(poison_duration,
                                                                                  [enemy_id, poison_power](const turn_callback_info& info) mutable {

                                                                                      sender::send(make_action_message(
                                                                                              "poison",
                                                                                              board::index_for(
                                                                                                      enemy_id)));

                                                                                      damage_dealers::standard_damage_dealer(special_damage(poison_power, enemy_id));

                                                                                      if (info.ended) {

                                                                                          if (entity_manager::alive(enemy_id)) {
                                                                                              remove_effect(enemy_id,
                                                                                                            "poisoned");
                                                                                          }
                                                                                      }
                                                                                  });

        auto poison_effect = make_negative_effect("poisoned");
        poison_effect->set_turn_connection(std::move(poisoned_connection));

        add_effect(enemy_id, poison_effect);
    }

    auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();

    auto moveable_ptr = std::dynamic_pointer_cast<moveable_base>(abilities_ptr->of_type(ability_types::moving));
    if (moveable_ptr) {
        moveable_ptr->refresh_range();
    }

    used = true;
}

std::string poisoned_missile::hint() const {

    std::string desc;
    desc = "Poisoned Missile - deals damage of " + std::to_string(damage) + "\n"
           " and poisons the opponent for " + std::to_string(poison_duration) + " turn."
            "Poison deals " + std::to_string(poison_power) + " damage per turn.";

    return std::move(desc);
}