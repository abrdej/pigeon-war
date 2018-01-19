#include <core/animations_queue.h>
#include <sender.h>
#include <core/board_effects.h>
#include "moveable.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "core/board.h"

void moveable::prepare(std::uint32_t for_index)
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
	states::state_controller::wait_for_action([this](std::uint32_t index)
											  {
												  return move(index);
											  });
}

void moveable::move(std::uint32_t index_to)
{
	if (used) {
        return;
    }

	std::uint32_t i = 0;
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

	remove_auras(move_from_index);

	for (auto&& effect_ptr : effects) {
		effect_ptr->remove_effect(entity_id);
	}

	sender::send(message_types::animation, animation_def::move, move_from_index, index_to);


	std::int32_t from_col = board::to_pos(move_from_index).first;
	std::int32_t to_col = board::to_pos(index_to).first;

	board::give_back(entity_id, index_to);

	states::state_controller::selected_index_ = index_to;
	states::state_controller::possible_movements_.clear();

	// aura stuff -> should be move from there

	for (auto&& aura : auras) {
		set_aura(index_to, aura);
	}


	effects = board_effects::get_effects(index_to);
	for (auto&& effect_ptr : effects) {
		effect_ptr->set_effect(entity_id);
	}

	used = true;
}

void aura_setter::set_aura(std::uint32_t index, const std::shared_ptr<effect>& aura) {
	std::vector<std::uint32_t> neighbors;
	board_helper::neighboring_fields(index, neighbors, false);

	for (auto&& neighbour_index : neighbors) {
		auto effect_id = board_effects::put_effect(neighbour_index, aura);
		effect_ids.push_back(effect_id);
	}
}

void aura_setter::remove_auras(std::uint32_t index) {
	for (auto&& effect_id : effect_ids) {
		board_effects::remove_effect(index, effect_id);
	}
	effect_ids.clear();
}