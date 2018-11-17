#include "drain.h"

#include <abilities/damage_dealers.h>
#include <components/damage_taker.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <core/path_finder.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include <server/sender.h>

drain::drain(std::uint32_t entity_id) : entity_id(entity_id) {}

void drain::use(std::uint32_t index_on)
{
	if (used) {
		return;
	}

	sender::send(make_action_message("drain", entity_id, index_on));

	damage_dealers::standard_damage_dealer(damage_pack(damage,
													   damage_types::MELEE,
													   game_board().at(index_on),
													   entity_id));

	standard_healing(healing_above_base_health(drain_amount, entity_id));

	used = true;
}
