#include <sender.h>
#include <common/animations.h>
#include <core/board.h>
#include <managers/players_manager.h>
#include "portal.h"
#include "possible_move_helper.h"

void portal::prepare(std::uint32_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::all_free(states::state_controller::possible_movements_);

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this, for_index](std::uint32_t index)
											  {
												  return use(for_index, index);
											  });
}

void portal::use(std::uint32_t from_index, std::uint32_t to_index) {
	if (used)
		return;

	auto center_pos = board::to_pos(from_index);
	auto destination_pos = board::to_pos(to_index);

	std::vector<std::uint32_t> around_fields_ids;
	board_helper::neighboring_fields(from_index, around_fields_ids, false);

	for (auto&& field_id : around_fields_ids) {
		if (!board::empty(field_id) && !players_funcs::neutral_entity(field_id)) {

			auto pos = board::to_pos(field_id);

			auto x_diff = center_pos.first - pos.first;
			auto y_diff = center_pos.second - pos.second;

			auto x_dest = destination_pos.first - x_diff;
			auto y_dest = destination_pos.second - y_diff;

			auto dest_index = board::to_index(x_dest, y_dest);

			if (board::empty(dest_index)) {
				board::move(field_id, dest_index);
			}
		}
	}

	board::move(from_index, to_index);

	sender::send(message_types::animation, animation_def::teleport, from_index, to_index);





	states::state_controller::selected_index_ = to_index;

	//used = true;
}