#include "tongue_of_fire.h"

#include <abilities/damage_dealers.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <core/path_finder.h>
#include <messages/make_message.h>
#include <server/sender.h>

tongue_of_fire::tongue_of_fire(std::uint32_t entity_id) : entity_id(entity_id) {}

void tongue_of_fire::use(std::uint32_t index_on)
{
	if (used)
		return;

	sender::send(make_action_message("tongue_of_fire", game_control().selected_index_, index_on));

	damage_dealers::standard_damage_dealer(ranged_damage(damage, game_board().at(index_on), entity_id));

	used = true;
}
