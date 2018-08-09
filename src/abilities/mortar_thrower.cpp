#include "mortar_thrower.h"

#include <server/sender.h>
#include <messages/make_message.h>
#include <managers/entity_manager.h>
#include "rocket_launcher.h"
#include "damage_dealers.h"
#include "core/board.h"
#include "abilities.h"

void mortar_thrower::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = game_control().selected_index_;
    auto entity_id = game_board().at(used_from_index);

    auto rocket_launcher_ptr = game::get<entity_manager>().get(entity_id).get<abilities>()->get<rocket_launcher>();
    if (rocket_launcher_ptr->was_used())
        return;

    bool has_bonus = *game::get<entity_manager>().get(entity_id).get<rocket_types>() != rocket_types::explosive_mortar;
    *game::get<entity_manager>().get(entity_id).get<rocket_types>() = rocket_types::explosive_mortar;

    std::cout << "has_bonus: " << has_bonus << "\n";

    std::int32_t real_damage = base_damage + (has_bonus ? rocket_change_bonus : 0);

    std::vector<std::uint32_t> neighbors;
    board_helper::neighboring_fields(index_on, neighbors, false);

    sender::send(make_action_message("flame_thrower", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(index_on), entity_id));

    for (auto& index : neighbors)
    {
        if (!game_board().empty(index))
            damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(index), entity_id));
    }

    used = true;
}