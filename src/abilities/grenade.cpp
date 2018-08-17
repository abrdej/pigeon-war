#include "grenade.h"

#include <core/game_controller.h>
#include <core/path_finder.h>
#include <abilities/damage_dealers.h>
#include <messages/make_message.h>
#include <server/sender.h>

grenade::grenade(std::uint32_t entity_id) : entity_id(entity_id) {}

void grenade::use(std::uint32_t on_index)
{
	if (used)
		return;

	used = true;

	std::vector<std::uint32_t> neighbors;
	board_helper::neighboring_fields(on_index, neighbors, false);

	sender::send(make_action_message("grenade", game_control().selected_index_, on_index));

	damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(on_index), entity_id));

	for (auto index : neighbors) {
		if (!game_board().empty(index)) {
			damage_dealers::standard_damage_dealer(ranged_damage(damage / 2, game_board().at(index), entity_id));
		}
	}
}
