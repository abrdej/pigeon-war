#include <core/path_finder.h>
#include <core/states.h>
#include <animation/animation.h>
#include "teleport.h"
#include "core/board.h"

teleport::teleport() {

}

void teleport::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(false);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range_);

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

	animation::player<animation::flash_bitmap>::launch(
			animation::flash_bitmap(for_index, std::chrono::milliseconds(100), "teleport.png"));
	animation::base_player::play();



	animation::player<animation::flash_bitmap>::launch(
			animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "teleport.png"));
	animation::base_player::play();

	board::give_back(entity_id, index_on);
	states::state_controller::selected_index_ = index_on;

	used = true;
}