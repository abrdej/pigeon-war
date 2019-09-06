#include <abilities/teleport.h>

#include <core/board.h>
#include <core/game_controller.h>

void teleport::prepare(std::uint32_t for_index) {

	game_control().selected_index_ = for_index;

	board_helper::all_free(game_control().possible_movements_);

	game_control().actual_targeting_type_ = target_types::moving;
	game_control().wait_for_action([this, for_index](std::uint32_t index)
											  {
												  return use(for_index, index);
											  });
}

void teleport::use(std::uint32_t from_index, std::uint32_t to_index) {

	if (used)
		return;

	sender::send(make_action_message("teleport", game_board().at(from_index), to_index));

	game_board().move(from_index, to_index);

	game_control().selected_index_ = to_index;

	used = true;
}
