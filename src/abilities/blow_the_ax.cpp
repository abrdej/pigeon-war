#include <core/game_controller.h>
#include <messages/make_message.h>
#include "blow_the_ax.h"
#include "damage_dealers.h"
#include "server/sender.h"

void blow_the_ax::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = game_control().selected_index_;

    auto entity_id = game_board().at(used_from_index);

    sender::send(make_action_message("blow_the_ax", entity_id, index_on));

    damage_dealers::standard_damage_dealer(melee_damage(damage, game_board().at(index_on), entity_id));

    used = true;
}