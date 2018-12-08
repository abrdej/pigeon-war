#include <abilities/claws.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>

void claws::use(std::uint32_t index_on) {
    if (used) {
        return;
    }

    auto caster_id = game_board().at(game_control().selected_index_);

    sender::send(make_action_message("claws", caster_id, index_on));

    auto enemy_id = game_board().at(index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    used = true;
}
