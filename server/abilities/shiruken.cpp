#include <core/states_controller.h>
#include <managers/additions_manager.h>
#include "shiruken.h"
#include "damage_dealers.h"

void shiruken::use(size_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    auto enemy_id = board::at(index_on);

    auto death_mark_receiver =
            turn::turn_system::every_round([this, enemy_id, counter = 0, duration = death_mark_duration]() mutable {
                if (++counter == duration) {
                    additions_manager::remove_component(enemy_id,
                                                        "death_mark");
                }
            });

    additions_manager::add_component(enemy_id,
                                     "death_mark",
                                     death_mark_receiver);

    used = true;
}

void shiruken::play_animation(size_t from_index, size_t to_index) {
    animations_queue::push_animation(animation_types::move,
                                     from_index,
                                     to_index,
                                     -1,
                                     bitmap_key::shiruken);

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     to_index,
                                     150,
                                     -1,
                                     bitmap_key::shiruken_splash);
}