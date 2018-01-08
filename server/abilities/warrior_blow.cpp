#include <core/states_controller.h>
#include "warrior_blow.h"
#include "damage_dealers.h"

void warrior_blow::use(size_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;


    play_animation(used_from_index, index_on);

    auto enemy_id = board::at(index_on);

    auto caster_id = board::at(used_from_index);
    auto health_pack = healths_manager::component_for(caster_id);

    auto missing_health = health_pack.base_health - health_pack.health;

    auto damage_increase_factor = missing_health / 5;

    auto final_damage = damage_increase_factor * damage_per_factor + damage;

    damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

    used = true;
}

void warrior_blow::play_animation(size_t index_from, size_t index_on) {

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
                                     bitmap_key::warrior_attack);

    animations_queue::push_animation(animation_types::move,
                                     index_on,
                                     index_from,
                                     entity_id,
                                     bitmap_key::none);

    board::give_back(entity_id, index_from);
}