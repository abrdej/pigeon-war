#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include "drain.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

void drain::use(std::uint32_t index_on)
{
	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	sender::send(message_types::animation, animation_def::drain, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(damage_pack(damage,
													   damage_types::MELEE,
													   board::at(index_on),
													   entity_id));

	entity_manager::get(entity_id).get<damage_taker>()->heal(healing(drain_amount,
																	 entity_id));
	used = true;
}

std::string drain::hint() const {

	std::string desc;
	desc = "Drain - deals damage of: " + std::to_string(damage) + " and heals native by: " + std::to_string(drain_amount) + " regardless of dealt damage.\n"
			"This skill can heal over the base level of health.";
	return std::move(desc);
}