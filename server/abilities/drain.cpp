#include "drain.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "managers/health_manager.h"

void drain::use(size_t index_on)
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

	healths_manager::receive_damage(healing(drain_amount,
											entity_id));
	used = true;
}

std::string drain::hint() const {

	std::string desc;
	desc = "Shoot - the shooter can give a double shot of: " +
		   std::to_string(damage) + " damage.\n" +
		   "\nRange: " + std::to_string(range) + ".";
	return std::move(desc);
}