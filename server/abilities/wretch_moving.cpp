#include <core/states_controller.h>
#include <core/board.h>
#include <sender.h>
#include <components/power_field.h>
#include <common/animations.h>
#include <managers/entity_manager.h>
#include <common/make_message.h>
#include "wretch_moving.h"

wretch_moving::wretch_moving(std::uint32_t entity_id) : entity_id(entity_id) {
    after_player_turn(entity_id, [this]() {
        used = false;
        range = max_range;
        auto power_field_ptr = entity_manager::get(this->entity_id).get<power_filed>();
        power_field_ptr->power = power_field_ptr->max_power;

        std::cout << "set power: " << power_field_ptr->max_power << "\n";
    });
}

void wretch_moving::prepare(std::uint32_t for_index) {
    states::state_controller::selected_index_ = for_index;
    states::state_controller::actual_state_ = states::states_types::wait_for_action;

    auto power = entity_manager::get(entity_id).get<power_filed>()->power;

    std::cout << "power: " << power << "\n";

    path_finder path_finder;
    path_finder.calc(for_index);
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       states::state_controller::possible_movements_costs_,
                                       used ? 0 : std::min(range, power));

    states::state_controller::actual_targeting_type_ = target_types::moving;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return move(index);
                                              });
}

void wretch_moving::move(std::uint32_t index_to) {
    if (used) {
        return;
    }

    std::uint32_t i = 0;
    for ( ; i < states::state_controller::possible_movements_.size(); ++i) {
        if (states::state_controller::possible_movements_[i] == index_to)
            break;
    }
    std::int32_t cost = states::state_controller::possible_movements_costs_[i];
    std::cout << "cost: " << cost << "\n";

    entity_manager::get(entity_id).get<power_filed>()->power -= power_decrease_for_cost * cost;

    range = 0;

    auto move_from_index = states::state_controller::selected_index_;

    auto taken_id = board::take(move_from_index);

    states::state_controller::selected_index_ = states::no_selected_index;

    sender::send(make_action_message("move", move_from_index, index_to));

    board::give_back(taken_id, index_to);

    states::state_controller::selected_index_ = index_to;
    states::state_controller::possible_movements_.clear();

    used = true;
}