#include <core/states_controller.h>
#include "magic_bullet.h"
#include "damage_dealers.h"

magic_bullet::magic_bullet(std::size_t entity_id) {
    onEveryTurn([this, entity_id]() {

        if (players_manager::get_active_player_id() == players_manager::player_for_entity(entity_id)) {
            used = false;
            magic_power += magic_power_accumulation_amount;

            std::vector<size_t> neighbors;
            board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);
            for (auto& index : neighbors)
            {
                if (!board::empty(index) && players_funcs::enemy_entity(index)) {
                    magic_power += magic_power_drain_amount;

                    animations_queue::push_animation(animation_types::flash_bitmap,
                                                     index,
                                                     150,
                                                     0,
                                                     bitmap_key::magic_suck);
                }
            }
        }
    });

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto half_damage = static_cast<int>(dmg.damage_value * 0.5f);

        //auto damage_for_magic_power = std::min<int>(static_cast<int>(0.5 * magic_power), dmg.damage_value);
        auto damage_for_magic_power = std::min<int>(magic_power, half_damage);
        magic_power -= damage_for_magic_power;

//        auto remaining_damage = dmg.damage_value - damage_for_magic_power;
        auto remaining_damage = half_damage + half_damage - damage_for_magic_power;

        auto final_damage = std::min(health_pack.health, remaining_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

void magic_bullet::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(magic_power, board::at(index_on), entity_id));

    magic_power = 0;

    used = true;
}

void magic_bullet::play_animation(size_t from_index, size_t to_index) {
    animations_queue::push_animation(animation_types::flash_bitmap,
                                     from_index,
                                     100,
                                     0,
                                     bitmap_key::monk_use_1);
    animations_queue::push_animation(animation_types::flash_bitmap,
                                     from_index,
                                     100,
                                     0,
                                     bitmap_key::monk_use_1);
    animations_queue::push_animation(animation_types::flash_bitmap,
                                     from_index,
                                     100,
                                     0,
                                     bitmap_key::monk_use_1);
    animations_queue::push_animation(animation_types::flash_bitmap,
                                     to_index,
                                     150,
                                     0,
                                     bitmap_key::magic_splash);
}