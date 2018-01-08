#include <managers/additions_manager.h>
#include "giant_blow.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

void giant_blow::use(size_t index_on)
{
    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    if (counter++ == 2) {
        states::state_controller::custom_valid_targets[enemy_id].insert(caster_id);

        auto giant_only_target =
                turn::turn_system::every_turn([this, enemy_id, counter = 0]() mutable {

                    if (++counter == 2) {

                        states::state_controller::custom_valid_targets[enemy_id].clear();

                        additions_manager::remove_component(enemy_id,
                                                            "giant_only_target");
                    }
                });

        additions_manager::add_component(enemy_id, "giant_only_target", giant_only_target);

        counter = 0;
    }

    used = true;
}

void giant_blow::play_animation(size_t index_from, size_t index_on)
{
    auto entity_id = board::take(index_from);

    animations_queue::push_animation(animation_types::move,
                                     index_from,
                                     index_on,
                                     entity_id,
                                     bitmap_key::none);

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     index_on,
                                     150,
                                     0,
                                     bitmap_key::giant_blow);

    animations_queue::push_animation(animation_types::move,
                                     index_on,
                                     index_from,
                                     entity_id,
                                     bitmap_key::none);

    board::give_back(entity_id, index_from);
}