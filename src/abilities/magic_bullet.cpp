#include <core/game_controller.h>
#include <components/damage_taker.h>
#include <messages/make_message.h>
#include <components/power_field.h>
#include "magic_bullet.h"
#include "damage_dealers.h"
#include "server/sender.h"
#include "managers/players_manager.h"

magic_bullet::magic_bullet(std::uint32_t entity_id)
        : entity_id(entity_id) {
    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

    after_player_turn(entity_id, [this, entity_id, power]() {
        if (first_used) {
            used = false;
//            magic_power += magic_power_accumulation_amount;
            power->power += magic_power_accumulation_amount;

            std::vector<std::uint32_t> neighbors;
            board_helper::neighboring_fields(game_board().index_for(entity_id), neighbors, false);
            for (auto& index : neighbors)
            {
                if (!game_board().empty(index) && players_funcs::enemy_entity(index)) {
                    power->power += magic_power_drain_amount;
//                    magic_power += magic_power_drain_amount;
                    sender::send(make_action_message("magic_suck", index));
                }
            }
        }
    });

    set_damage_receiver(entity_id, [this, entity_id, power](health_field& health_pack, const damage_pack& dmg) mutable {

        auto half_damage = static_cast<std::int32_t>(dmg.damage_value * 0.5f);

        //auto damage_for_magic_power = std::min<std::int32_t>(static_cast<std::int32_t>(0.5 * magic_power), dmg.damage_value);
        auto damage_for_magic_power = std::min<std::int32_t>(power->power, half_damage);
//        magic_power -= damage_for_magic_power;
        power->power -= damage_for_magic_power;
        sender::send(make_action_message("change_power",
                                         game_board().index_for(entity_id), damage_for_magic_power));

//        auto remaining_damage = dmg.damage_value - damage_for_magic_power;
        auto remaining_damage = half_damage + half_damage - damage_for_magic_power;

        auto final_damage = std::min(health_pack.health, remaining_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

std::string magic_bullet::hint() const {

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

    std::string desc;
    desc = "Magic Bullet - monk accumulates " + std::to_string(magic_power_accumulation_amount) +
            " magic points for each turn.\n"
            "In addition, he accumulates " + std::to_string(magic_power_drain_amount) +
            " magic points for each enemy in his neighborhood.\n"
            "Magic point can be used to deal damage equal to the amount of magic points.\n"
            "Additionally, half of the damage that monk receive firstly must destroys\n"
                    " the magic shiled which is formed from this points.\n"
            "Magic power: " + std::to_string(power->power) + ".";

    return std::move(desc);
}

void magic_bullet::use(std::uint32_t index_on) {

    if (used)
        return;

    auto from_index = game_control().selected_index_;

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();


    sender::send(make_action_message("magic_bullet", from_index, index_on));

    damage_dealers::standard_damage_dealer(magic_damage(power->power, game_board().at(index_on), game_board().at(from_index)));

    auto change_power = -power->power;
    power->power = 0;

    sender::send(make_action_message("change_power", from_index, change_power));

    first_used = true;

    used = true;
}