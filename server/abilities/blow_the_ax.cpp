#include <core/states_controller.h>
#include <common/make_message.h>
#include "blow_the_ax.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

void blow_the_ax::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto entity_id = board::at(used_from_index);

    sender::send(make_action_message("blow_the_ax", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(index_on), entity_id));

    used = true;
}