#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include "managers/additions_manager.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"

void poisoned_missile::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(from_index);

    sender::send(message_types::animation, animation_def::poisoned_missile, from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    auto poison_receiver =
            turn::turn_system::every_turn([this, enemy_id, poison_damage = poison_power, counter = 0, pl = poison_last]() mutable {

                if (counter++ % 2) {
                    damage_dealers::standard_damage_dealer(special_damage(poison_damage, enemy_id));
                    if (counter == pl * 2) {
                        if (entity_manager::alive(enemy_id)) {
                            additions_manager::remove_component(enemy_id,
                                                                "poison");
                        }
                    }
                }
    });


    additions_manager::add_component(enemy_id,
                                     "poison",
                                     poison_receiver);

    auto& abilities = abilities_manager::component_for(entity_id);
    auto moveable_ptr = std::static_pointer_cast<moveable>(abilities.type(abilities::ability_types::moving));
    moveable_ptr->refresh_range();

    used = true;
}

std::string poisoned_missile::hint() const {

    std::string desc;
    desc = "Poisoned Missile - deals damage of " + std::to_string(damage) + "\n"
           " and poisons the opponent for " + std::to_string(poison_last) + " turn."
            "Poison deals " + std::to_string(poison_power) + " damage per turn.";

    return std::move(desc);
}