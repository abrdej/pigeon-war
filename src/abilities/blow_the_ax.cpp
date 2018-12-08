#include <abilities/blow_the_ax.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>

blow_the_ax::blow_the_ax(std::uint32_t entity_id) : entity_id(entity_id) {}

void blow_the_ax::use(std::uint32_t on_index) {
    if (used)
        return;

    sender::send(make_action_message("blow_the_ax", entity_id, on_index));
    damage_dealers::standard_damage_dealer(melee_damage(damage, game_board().at(on_index), entity_id));

    used = true;
}
