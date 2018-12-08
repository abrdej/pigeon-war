#include "mortar_thrower.h"

#include <abilities/abilities.h>
#include <abilities/damage_dealers.h>
#include <abilities/rocket_launcher.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <server/sender.h>

mortar_thrower::mortar_thrower(std::uint32_t entity_id) : entity_id(entity_id) {}

void mortar_thrower::use(std::uint32_t on_index) {

    if (used)
        return;

    auto used_from_index = game_control().selected_index_;

    auto rocket_launcher_ptr = game::get<entity_manager>().get(entity_id).get<abilities>()->get<rocket_launcher>();
    if (rocket_launcher_ptr->was_used())
        return;

    bool has_bonus = *game::get<entity_manager>().get(entity_id).get<rocket_types>() != rocket_types::explosive_mortar;
    *game::get<entity_manager>().get(entity_id).get<rocket_types>() = rocket_types::explosive_mortar;

    auto real_damage = base_damage + (has_bonus ? rocket_change_bonus : 0);

    std::vector<std::uint32_t> neighbors;
    board_helper::neighboring_fields(on_index, neighbors, false);

    sender::send(make_action_message("flame_thrower", used_from_index, on_index));

    damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(on_index), entity_id));

    for (auto index : neighbors) {
        if (!game_board().empty(index))
            damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(index), entity_id));
    }

    used = true;
}
