#include "flame_burning.h"
#include "damage_dealers.h"

#include <core/board.h>
#include <messages/massages_makers.h>
#include <server/sender.h>
#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <components/damage_taker.h>

flame_burning::flame_burning(std::uint32_t entity_id) {

}

void flame_burning::use(std::uint32_t index_on) {
    if (used)
        return;

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);
    auto enemy_id = game_board().at(index_on);

    sender::send(make_action_message("flame_burning", used_from_index, index_on));

    auto final_damage = damage;

    if (game::get<entity_manager>().get(enemy_id).contain<power_filed>()) {

        LOG(debug) << "here flame_burning";

        auto magic_burning = std::min(game::get<entity_manager>().get(enemy_id).get<power_filed>()->power, burn_magic_power);
        auto& power = game::get<entity_manager>().get(enemy_id).get<power_filed>()->power;

        auto power_decrease = std::min(power, magic_burning);

        power -= power_decrease;
        play_power_change_animation(index_on, power_decrease);
        final_damage += magic_burning;
    }

    damage_dealers::standard_damage_dealer(magic_damage(final_damage, enemy_id, caster_id));

    used = true;
}