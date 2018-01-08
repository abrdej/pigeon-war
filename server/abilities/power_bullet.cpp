#include <managers/additions_manager.h>
#include "power_bullet.h"
#include "core/states_controller.h"
#include "managers/abilities_manager.h"
#include "damage_dealers.h"

void power_bullet::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(damage_per_turn, board::at(index_on), caster_id));

    auto enemy_id = board::at(index_on);

    auto damage_per_turn_receiver =
            turn::turn_system::every_turn([enemy_id, caster_id, counter = 0,
                                                  damage = damage_per_turn,
                                                  max_counter = turn_for_additional_damage]() mutable {

                if (++counter == max_counter) {

                    animations_queue::push_animation(animation_types::flash_bitmap,
                                                     board::index_for(enemy_id),
                                                     150,
                                                     0,
                                                     bitmap_key::power_bullet_bum);

                    damage_dealers::standard_damage_dealer(magic_damage(damage, enemy_id, caster_id));

                    additions_manager::remove_component(enemy_id,
                                                            "damage_per_turn");
                }
            });


    additions_manager::add_component(enemy_id,
                                     "damage_per_turn",
                                     damage_per_turn_receiver);

    used = true;
}

void power_bullet::play_animation(size_t from_index, size_t to_index) {
    animations_queue::push_animation(animation_types::move,
                                     from_index,
                                     to_index,
                                     -1,
                                     bitmap_key::power_bullet);

    animations_queue::push_animation(animation_types::flash_bitmap,
                                     to_index,
                                     150,
                                     0,
                                     bitmap_key::power_bullet_bum);
}
