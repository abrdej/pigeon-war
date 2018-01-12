#include <core/path_finder.h>
#include <core/states_controller.h>
#include <common/animations.h>
#include <core/animations_queue.h>
#include <sender.h>
#include "teleport.h"
#include "core/board.h"

void teleport::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::all_free(states::state_controller::possible_movements_);

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this, for_index](size_t index)
											  {
												  return use(for_index, index);
											  });
}

void teleport::use(size_t from_index, size_t to_index) {

	if (used)
		return;

	sender::send(message_types::animation, animation_def::teleport, from_index, to_index);

	board::move(from_index, to_index);

	states::state_controller::selected_index_ = to_index;

	used = true;
}

std::string teleport::hint() const {

	std::string desc;
	desc = "Teleport - teleports the droid to a selected place on the map.\n"
			"It can be used only once per battle.";

	return std::move(desc);
}