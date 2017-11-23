#include "states.h"
#include "board.h"
#include "managers/entity_manager.h"
#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "managers/abilities_manager.h"

namespace states
{
size_t state_controller::selected_index_ = -1;
states_types state_controller::actual_state_ = states_types::waiting;
target_types state_controller::actual_targeting_type_ = target_types::non;

std::vector<size_t> state_controller::possible_movements_;
std::vector<size_t> state_controller::movements_ranges_;
std::vector<size_t> state_controller::possible_movements_costs_;
std::function<void(size_t)> state_controller::caller_;

void state_controller::first_state(size_t select_from_index)
{
	if (select_from_index == no_selected_index)
		return;

	selected_index_ = select_from_index;
	size_t selected_index = states::state_controller::selected_index_;
	auto entity_id = board::at(selected_index);
	auto& entity_abilities = abilities_manager::component_for(entity_id);

	auto moveable = entity_abilities.at(0);
	if (moveable) {
		moveable->operator()(states::state_controller::selected_index_);
	}
}

void state_controller::wait_for_action(const std::function<void(size_t index)>& caller)
{
	state_controller::actual_state_ = states_types::wait_for_action;
	caller_ = caller;
}

void state_controller::do_action(size_t index)
{
	caller_(index);
}

bool state_controller::is_possible_movement(size_t index)
{
	auto begin_it = std::begin(states::state_controller::possible_movements_);
	auto end_it = std::end(states::state_controller::possible_movements_);
	auto result = std::find(begin_it, end_it, index);
	return result != end_it;
}
};