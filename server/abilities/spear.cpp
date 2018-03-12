#include <core/states_controller.h>
#include <common/make_message.h>
#include "spear.h"
#include "damage_dealers.h"
#include "sender.h"
#include "components/damage_taker.h"

spear::spear(std::uint32_t id) : entity_id(id) {
    on_receive_damage(entity_id, [this](const damage_pack& dmg) mutable {
       accumulated_damage += additional_damage;
    }, damage_taker::on_receive_damage_policy::after);
}

void spear::use(std::uint32_t index_on) {

    if (used)
        return;

    used = true;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(make_action_message("spear", used_from_index, index_on));

    std::int32_t full_damage = damage + accumulated_damage;

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