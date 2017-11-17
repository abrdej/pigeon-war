#include "moveable.h"
#include "core/states.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "animation/animation.h"
#include "managers/directions_manager.h"
#include "managers/types_manager.h"

void moveable::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

	path_finder path_finder;
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
		states::state_controller::possible_movements_costs_,
		range());

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return move(index);
	});
}

void moveable::move(size_t index_to)
{
	auto move_from_index = states::state_controller::selected_index_;

	auto end_it = std::end(states::state_controller::possible_movements_);
	auto begin_it = std::begin(states::state_controller::possible_movements_);
	auto result = std::find(begin_it, end_it, index_to);

	if (result != end_it)
	{
		auto entity_id = board::take(move_from_index);
		auto type = types_manager::component_for(entity_id);

		auto selected_index_backup = states::state_controller::selected_index_;
		states::state_controller::selected_index_ = states::no_selected_index;
		animation::player<animation::move>::launch(animation::move(move_from_index, index_to, type));
		animation::base_player::play();
		states::state_controller::selected_index_ = selected_index_backup;

		auto move_cost = states::state_controller::possible_movements_costs_[result - begin_it];
		use_move(move_cost);
		
		int from_col = board::to_col_row(move_from_index).first;
		int to_col = board::to_col_row(index_to).first;
		if (from_col != to_col)
			if (from_col - to_col < 0)
				directions_manager::turn_right(entity_id);
			else
				directions_manager::turn_left(entity_id);
		
		board::give_back(entity_id, index_to);

		states::state_controller::selected_index_ = index_to;
		states::state_controller::possible_movements_.clear();
		prepare(index_to);
	}
}