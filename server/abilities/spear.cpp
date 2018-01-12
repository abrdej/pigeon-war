#include <core/states_controller.h>
#include "spear.h"
#include "damage_dealers.h"

spear::spear(sf::Uint64 id) : entity_id(id) {
    healths_manager::on_receive_damage(entity_id, [this](const damage_pack& dmg) mutable {
       accumulated_damage += additional_damage;
    }, healths_manager::on_receive_damage_policy::after);
}

void spear::use(sf::Uint64 index_on) {

    if (used)
        return;

    used = true;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::spear, used_from_index, index_on);

    sf::Int32 full_damage = damage + accumulated_damage;

    damage_dealers::standard_damage_dealer(melee_damage(full_damage, board::at(index_on), entity_id));

    accumulated_damage = 0;
}

std::string spear::hint() const {

    std::string desc;
    desc = "Spear - deals damage of " + std::to_string(damage) + ".\n"
            "Additionally for every received attack, guardian accumulates "  + std::to_string(additional_damage) + " damage\n"
            "which is consumed in the next attack.\n"
            "Accumulated damage: " + std::to_string(accumulated_damage) + ".";

    return std::move(desc);
}