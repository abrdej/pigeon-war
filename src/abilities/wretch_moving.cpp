#include <core/game_controller.h>
#include <core/board.h>
#include <server/sender.h>
#include <components/power_field.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include "wretch_moving.h"

wretch_moving::wretch_moving(std::uint32_t entity_id) : entity_id(entity_id) {
    after_player_turn(entity_id, [this]() {
        used = false;
        range = max_range;
        auto power_field_ptr = game::get<entity_manager>().get(this->entity_id).get<power_filed>();
        power_field_ptr->power = power_field_ptr->max_power;

        std::cout << "set power: " << power_field_ptr->max_power << "\n";
    });
}

void wretch_moving::prepare(std::uint32_t for_index) {
    game_control().selected_index_ = for_index;
    game_control().actual_state_ = states_types::wait_for_action;

    auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

    std::cout << "power: " << power << "\n";

    path_finder path_finder;
    path_finder.calc(for_index);
    path_finder.get_possible_movements(game_control().possible_movements_,
                                       game_control().possible_movements_costs_,
                                       used ? 0 : std::min(range, power));

    game_control().actual_targeting_type_ = target_types::moving;
    game_control().wait_for_action([this](std::uint32_t index)
                                              {
                                                  return move(index);
                                              });
}

void wretch_moving::move(std::uint32_t index_to) {
    if (used) {
        return;
    }

    std::uint32_t i = 0;
    for ( ; i < game_control().possible_movements_.size(); ++i) {
        if (game_control().possible_movements_[i] == index_to)
            break;
    }
    std::int32_t cost = game_control().possible_movements_costs_[i];
    std::cout << "cost: " << cost << "\n";

    game::get<entity_manager>().get(entity_id).get<power_filed>()->power -= power_decrease_for_cost * cost;

    range = 0;

    auto move_from_index = game_control().selected_index_;

    auto taken_id = game_board().take(move_from_index);

    game_control().selected_index_ = no_selected_index;

//    sender::send(make_action_message("move", move_from_index, index_to));
    sender::send(make_action_message("move", taken_id, index_to));

    game_board().give_back(taken_id, index_to);

    game_control().selected_index_ = index_to;
    game_control().possible_movements_.clear();

    used = true;
}