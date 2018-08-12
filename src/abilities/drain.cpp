#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include <messages/make_message.h>
#include "drain.h"
#include "core/path_finder.h"
#include "core/game_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "server/sender.h"

void drain::use(std::uint32_t index_on)
{
	if (used) {
		return;
	}

	auto used_from_index = game_control().selected_index_;
	auto entity_id = game_board().at(used_from_index);

	sender::send(make_action_message("drain", entity_id, index_on));

	damage_dealers::standard_damage_dealer(damage_pack(damage,
													   damage_types::MELEE,
													   game_board().at(index_on),
													   entity_id));

	standard_healing(healing_above_base_health(drain_amount, entity_id));

	used = true;
}