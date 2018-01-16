#include <core/animations_queue.h>
#include <sender.h>
#include "moveable.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "core/board.h"

void moveable::prepare(std::uint64_t for_index)
{
	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

    if (type == types::path) {
        path_finder path_finder;
        path_finder.calc(for_index);
        path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                           states::state_controller::possible_movements_costs_,
										   used ? 0 : range);

    } else if (type == types::straight) {
        board_helper::calc_straight(states::state_controller::selected_index_,
                                states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
									used ? 0 : range);
    }

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this](std::uint64_t index)
											  {
												  return move(index);
											  });
}

void moveable::move(std::uint64_t index_to)
{
	if (used) {
        return;
    }

	std::uint64_t i = 0;
	for ( ; i < states::state_controller::possible_movements_.size(); ++i) {
		if (states::state_controller::possible_movements_[i] == index_to)
			break;
	}
	auto cost = static_cast<std::int32_t>(states::state_controller::possible_movements_costs_[i]);

	if (cost_callback)
		cost_callback(cost);

	auto move_from_index = states::state_controller::selected_index_;

	auto entity_id = board::take(move_from_index);

	states::state_controller::selected_index_ = states::no_selected_index;

	sender::send(message_types::animation, animation_def::move, move_from_index, index_to);


	std::int32_t from_col = board::to_pos(move_from_index).first;
	std::int32_t to_col = board::to_pos(index_to).first;

	board::give_back(entity_id, index_to);

	states::state_controller::selected_index_ = index_to;
	states::state_controller::possible_movements_.clear();

	used = true;
}