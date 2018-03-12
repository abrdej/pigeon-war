#include <core/path_finder.h>
#include <core/states_controller.h>
#include <sender.h>
#include <common/make_message.h>
#include "teleport.h"
#include "core/board.h"

void teleport::prepare(std::uint32_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::all_free(states::state_controller::possible_movements_);

	states::state_controller::actual_targeting_type_ = target_types::moving;
	states::state_controller::wait_for_action([this, for_index](std::uint32_t index)
											  {
												  return use(for_index, index);
											  });
}

void teleport::use(std::uint32_t from_index, std::uint32_t to_index) {

	if (used)
		return;

	sender::send(make_action_message("teleport", from_index, to_index));

	board::move(from_index, to_index);

	states::state_controller::selected_index_ = to_index;

	used = true;
}