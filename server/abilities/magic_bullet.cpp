#include <core/states_controller.h>
#include <components/damage_taker.h>
#include "magic_bullet.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

magic_bullet::magic_bullet(std::uint32_t entity_id) {
    onEveryTurn([this, entity_id]() {

        if (players_manager::get_active_player_id() == players_manager::player_for_entity(entity_id)) {
            used = false;
            magic_power += magic_power_accumulation_amount;

            std::vector<std::uint32_t> neighbors;
            board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);
            for (auto& index : neighbors)
            {
                if (!board::empty(index) && players_funcs::enemy_entity(index)) {

                    magic_power += magic_power_drain_amount;
                    sender::send(message_types::animation, animation_def::magic_suck, index);
                }
            }
        }
    });

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto half_damage = static_cast<std::int32_t>(dmg.damage_value * 0.5f);

        //auto damage_for_magic_power = std::min<std::int32_t>(static_cast<std::int32_t>(0.5 * magic_power), dmg.damage_value);
        auto damage_for_magic_power = std::min<std::int32_t>(magic_power, half_damage);
        magic_power -= damage_for_magic_power;

//        auto remaining_damage = dmg.damage_value - damage_for_magic_power;
        auto remaining_damage = half_damage + half_damage - damage_for_magic_power;

        auto final_damage = std::min(health_pack.health, remaining_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

std::string magic_bullet::hint() const {

    std::string desc;
    desc = "Magic Bullet - monk accumulates " + std::to_string(magic_power_accumulation_amount) +
            " magic points for each turn.\n"
            "In addition, he accumulates " + std::to_string(magic_power_drain_amount) +
            " magic points for each enemy in his neighborhood.\n"
            "Magic point can be used to deal damage equal to the amount of magic points.\n"
            "Additionally, half of the damage that monk receive firstly must destroys\n"
                    " the magic shiled which is formed from this points.";

    return std::move(desc);
}

void magic_bullet::use(std::uint32_t index_on) {

    if (used)
        return;

    auto from_index = states::state_controller::selected_index_;

    sender::send(message_types::animation, animation_def::magic_bullet, from_index, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(magic_power, board::at(index_on), board::at(from_index)));

    magic_power = 0;

    used = true;
}