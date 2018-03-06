#include "flame_burning.h"
#include "damage_dealers.h"

#include <core/board.h>
#include <common/make_message.h>
#include <sender.h>
#include <managers/entity_manager.h>
#include <components/power_field.h>

flame_burning::flame_burning(std::uint32_t entity_id) {

}

void flame_burning::use(std::uint32_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);
    auto enemy_id = board::at(index_on);

    sender::send(make_animation_message("flame_burning", used_from_index, index_on));

    auto final_damage = damage;

    if (entity_manager::get(enemy_id).contain<power_field>()) {
        auto magic_burning = std::min(entity_manager::get(enemy_id).get<power_field>()->power, burn_magic_power);
        entity_manager::get(enemy_id).get<power_field>()->power -= magic_burning;
        final_damage += magic_burning;
    }

    damage_dealers::standard_damage_dealer(magic_damage(final_damage, enemy_id, caster_id));

    used = true;
}