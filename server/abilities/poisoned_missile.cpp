#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include "components/additions.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"
#include "abilities/moveable.h"
#include "sender.h"
#include "common/animations.h"

void poisoned_missile::use(std::uint32_t index_on) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(from_index);

    sender::send(message_types::animation, animation_def::poisoned_missile, from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    if (entity_manager::alive(enemy_id)) {

        auto poison_power = this->poison_power;
        auto poison_duration = this->poison_duration;

        auto poison_receiver = make_every_two_turns_from_next_callback_holder(poison_duration,
                                                                              [enemy_id, poison_power](const turn_callback_info& info) mutable {

                                                                                  sender::send(message_types::animation, animation_def::poison, board::index_for(enemy_id));

                                                                                  damage_dealers::standard_damage_dealer(special_damage(poison_power, enemy_id));

                                                                                  if (info.ended) {

                                                                                      if (entity_manager::alive(enemy_id)) {
                                                                                          remove_component(enemy_id,
                                                                                                           "poison");
                                                                                      }
                                                                                  }
                                                                              });

        add_component(enemy_id,
                      "poison",
                      std::move(poison_receiver));
    }

    auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
    auto moveable_ptr = std::static_pointer_cast<moveable>(abilities_ptr->type(abilities::ability_types::moving));
    moveable_ptr->refresh_range();

    used = true;
}

std::string poisoned_missile::hint() const {

    std::string desc;
    desc = "Poisoned Missile - deals damage of " + std::to_string(damage) + "\n"
           " and poisons the opponent for " + std::to_string(poison_duration) + " turn."
            "Poison deals " + std::to_string(poison_power) + " damage per turn.";

    return std::move(desc);
}