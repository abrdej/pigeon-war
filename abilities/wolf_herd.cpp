#include "wolf_herd.h"
#include <core/states.h>

void wolf_herd::prepare(size_t for_index) {

	states::state_controller::actual_state_ = states::states_types::wait_for_action;
	states::state_controller::possible_movements_.push_back(for_index);
	states::state_controller::actual_targeting_type_ = states::target_types::caster;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void wolf_herd::use(size_t index_on) {

	if (used_)
		return;

	used_ = true;

//	auto shooter_id = entity_manager::create<shooter>();
//	auto samurai_id = entity_manager::create<samurai_rat>();
//	auto droid_id = entity_manager::create<droid>();
//
//	board::insert(board::to_index(2, 3), shooter_id);
//	board::insert(board::to_index(2, 5), samurai_id);
//	board::insert(board::to_index(2, 7), droid_id);
//
//	players::add_entity_for_player("tester2", saberhand_id);

}
