#include <core/states_controller.h>
#include <managers/entity_manager.h>
#include "managers/additions_manager.h"
#include "poisoned_missile.h"
#include "damage_dealers.h"

void poisoned_missile::use(size_t index_on) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(from_index);

    sender::send(message_types::animation, animation_def::poisoned_missile, from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    auto poison_receiver =
            turn::turn_system::every_turn([this, enemy_id, counter = 0, pl = poison_last]() mutable {

                if (counter++ % 2) {
                    damage_dealers::standard_damage_dealer(special_damage(5, enemy_id));
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