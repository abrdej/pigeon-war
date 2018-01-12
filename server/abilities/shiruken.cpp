#include <core/states_controller.h>
#include <managers/additions_manager.h>
#include "shiruken.h"
#include "damage_dealers.h"

void shiruken::use(sf::Uint64 index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    auto enemy_id = board::at(index_on);

    auto has_death_mark = additions_manager::has_component(enemy_id, "death_mark");

    sender::send(message_types::animation, animation_def::shiruken, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(has_death_mark ? damage + additional_damage_for_death_mark : damage, enemy_id, entity_id));


//    auto death_mark_receiver =
//            turn::turn_system::every_turn([this, enemy_id, counter = 0, duration = death_mark_duration]() mutable {
//                if (counter++ == duration * 2) {
//                    additions_manager::remove_component(enemy_id,
//                                                        "death_mark");
//                }
//            });
//
//    additions_manager::add_component(enemy_id,
//                                     "death_mark",
//                                     death_mark_receiver);

    used = true;
}