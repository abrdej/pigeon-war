#include <core/states_controller.h>
#include "blow_the_ax.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

std::string blow_the_ax::hint() const {
    std::string desc;
    desc = "Blow The Ax - deals damage of: " + std::to_string(damage) + " to single target.";
    return std::move(desc);
}

void blow_the_ax::use(std::uint64_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto entity_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::blow_the_ax, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(index_on), entity_id));

    used = true;
}