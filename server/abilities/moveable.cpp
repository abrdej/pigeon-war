#include <core/animations_queue.h>
#include "moveable.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "managers/directions_manager.h"

void moveable::prepare(sf::Uint64 for_index)
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
	states::state_controller::wait_for_action([this](sf::Uint64 index)
											  {
												  return move(index);
											  });
}

void moveable::move(sf::Uint64 index_to)
{
	if (used) {
        return;
    }

	sf::Uint64 i = 0;
	for ( ; i < states::state_controller::possible_movements_.size(); ++i) {
		if (states::state_controller::possible_movements_[i] == index_to)
			break;
	}
	auto cost = static_cast<sf::Int32>(states::state_controller::possible_movements_costs_[i]);

	if (cost_callback)
		cost_callback(cost);

	auto move_from_index = states::state_controller::selected_index_;

	auto entity_id = board::take(move_from_index);

	states::state_controller::selected_index_ = states::no_selected_index;

	sender::send(message_types::animation, animation_def::move, move_from_index, index_to);


	sf::Int32 from_col = board::to_pos(move_from_index).first;
	sf::Int32 to_col = board::to_pos(index_to).first;
	if (from_col != to_col)
		if (from_col - to_col < 0)
			directions_manager::turn_right(entity_id);
		else
			directions_manager::turn_left(entity_id);

	board::give_back(entity_id, index_to);

	states::state_controller::selected_index_ = index_to;
	states::state_controller::possible_movements_.clear();

	used = true;
}