#include "poke.h"

#include <abilities/damage_dealers.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <messages/make_message.h>
#include <server/sender.h>

void poke::use(std::uint32_t index_on)
{
    if (used) {
        return;
    }

    auto caster_id = game_board().at(game_control().selected_index_);

    sender::send(make_action_message("poke", caster_id, index_on));

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    used = true;
}