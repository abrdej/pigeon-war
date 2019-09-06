#include "spear.h"

#include <abilities/damage_dealers.h>
#include <components/damage_taker.h>
#include <core/game_controller.h>
#include <messages/massages_makers.h>
#include <server/sender.h>

spear::spear(std::uint32_t id) : entity_id(id) {
    on_receive_damage(entity_id, [this](const damage_pack& dmg) mutable {
       accumulated_damage += additional_damage;
    }, on_receive_damage_policy::after);
}

void spear::use(std::uint32_t on_index) {

    if (used)
        return;

    sender::send(make_action_message("spear", entity_id, on_index));

    std::int32_t full_damage = damage + accumulated_damage;

    damage_dealers::standard_damage_dealer(melee_damage(full_damage, game_board().at(on_index), entity_id));

    accumulated_damage = 0;

    used = true;
}
