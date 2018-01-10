#include <core/states_controller.h>
#include "spear.h"
#include "damage_dealers.h"

spear::spear(std::size_t id) : entity_id(id) {
    healths_manager::on_receive_damage(entity_id, [this](const damage_pack& dmg) mutable {
       accumulated_damage += 4;
    }, healths_manager::on_receive_damage_policy::after);
}

void spear::use(size_t index_on) {

    if (used)
        return;

    used = true;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::spear, used_from_index, index_on);

    int full_damage = damage + accumulated_damage;

    damage_dealers::standard_damage_dealer(melee_damage(full_damage, board::at(index_on), entity_id));

    accumulated_damage = 0;
}