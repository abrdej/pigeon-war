#include "flame_thrower.h"
#include "damage_dealers.h"
#include <core/path_finder.h>
#include <core/game_controller.h>
#include <messages/massages_makers.h>
#include "server/sender.h"
#include <core/board.h>

void flame_thrower::use(std::uint32_t index_on) {

	if (used)
		return;

	std::int32_t real_damage = damage;

	if (counter == 2) {
		real_damage += damage_bonus;
		counter = 0;
	}

	used = true;
	auto used_from_index = game_control().selected_index_;
	auto entity_id = game_board().at(used_from_index);

	std::vector<std::uint32_t> neightbords;
	board_helper::neighboring_fields(index_on, neightbords, false);

	sender::send(make_action_message("flame_thrower", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(index_on), entity_id));

	for (auto& index : neightbords)
	{
		if (!game_board().empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(real_damage, game_board().at(index), entity_id));
	}

	++counter;
}