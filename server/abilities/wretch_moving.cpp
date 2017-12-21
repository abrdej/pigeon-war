#include <core/states_controller.h>
#include <core/board.h>
#include <managers/directions_manager.h>
#include "wretch_moving.h"

wretch_moving::wretch_moving(std::size_t entity_id) : entity_id(entity_id) {
    onEveryRound([this]() {
        used = false;
        range = max_range;
        powers_manager::set_power_to_base_power(this->entity_id);
    });
}

void wretch_moving::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;
    states::state_controller::actual_state_ = states::states_types::wait_for_action;

    int power = powers_manager::get_power_for(entity_id);

    std::cout << "power: " << power << "\n";

    path_finder path_finder;
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       used ? 0 : std::min(range, power));

    states::state_controller::actual_targeting_type_ = states::target_types::moving;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return move(index);
                                              });
}

void wretch_moving::move(size_t index_to) {
    if (used) {
        return;
    }

    std::size_t i = 0;
    for ( ; i < states::state_controller::possible_movements_.size(); ++i) {
        if (states::state_controller::possible_movements_[i] == index_to)
            break;
    }
    auto cost = states::state_controller::possible_movements_costs_[i];
    std::cout << "cost: " << cost << "\n";

    powers_manager::modify_power_by(entity_id, -power_decrease_for_cost * cost);
    range = 0;

    auto move_from_index = states::state_controller::selected_index_;

    auto taken_id = board::take(move_from_index);

    states::state_controller::selected_index_ = states::no_selected_index;

    animations_queue::push_animation(animation_types::move,
                                     move_from_index,
                                     index_to,
                                     taken_id,
                                     bitmap_key::none);

    int from_col = board::to_pos(move_from_index).first;
    int to_col = board::to_pos(index_to).first;
    if (from_col != to_col)
        if (from_col - to_col < 0)
            directions_manager::turn_right(taken_id);
        else
            directions_manager::turn_left(taken_id);

    board::give_back(taken_id, index_to);

    states::state_controller::selected_index_ = index_to;
    states::state_controller::possible_movements_.clear();

    used = true;
}