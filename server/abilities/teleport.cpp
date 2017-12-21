#include <core/path_finder.h>
#include <core/states_controller.h>
#include <common/animations.h>
#include <core/animations_queue.h>
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

void teleport::use(size_t for_index, size_t index_on) {

	if (used)
		return;

	auto entity_id = board::take(for_index);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 for_index,
									 100,
									 entity_id,
									 bitmap_key::teleport);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 index_on,
									 150,
									 entity_id,
									 bitmap_key::teleport);

	board::give_back(entity_id, index_on);
	states::state_controller::selected_index_ = index_on;

	used = true;
}