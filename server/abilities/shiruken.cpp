#include <core/states_controller.h>
#include <components/applied_effects.h>
#include <common/make_message.h>
#include "shiruken.h"
#include "damage_dealers.h"
#include "sender.h"

void shiruken::use(std::uint32_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    auto enemy_id = board::at(index_on);

    auto has_death_mark = has_effect(enemy_id, "death_mark");

    sender::send(make_action_message("shiruken", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(ranged_damage(has_death_mark ? damage + additional_damage_for_death_mark : damage, enemy_id, entity_id));


//    auto death_mark_receiver =
//            turn_system::every_turn([this, enemy_id, counter = 0, duration = death_mark_duration]() mutable {
//                if (counter++ == duration * 2) {
//                    remove_effect(enemy_id,
//                                                        "death_mark");
//                }
//            });
//
//    add_effect(enemy_id,
//                                     "death_mark",
//                                     death_mark_receiver);

    used = true;
}