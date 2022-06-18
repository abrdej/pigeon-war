#include <poke.h>

#include <turn_based/damage_dealers.h>
#include <turn_based/board.h>
#include <turn_based/game_controller.h>
#include <messages/massages_makers.h>
#include <turn_based/sender.h>

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