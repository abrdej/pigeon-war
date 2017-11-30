#include <core/states.h>
#include <animation/animation.h>
#include "blow_the_ax.h"
#include "damage_dealers.h"
#include "managers/types_manager.h"

blow_the_ax::blow_the_ax() {
    onEveryRound([this]() {
        used = false;
    });
}

void blow_the_ax::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                1);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void blow_the_ax::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;

    auto entity_id = board::take(used_from_index);
    auto type = types_manager::component_for(entity_id);
    animation::player<animation::move>::launch(animation::move(used_from_index, index_on, type));
    animation::base_player::play();
    //animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "claws.png"));
    //animation::base_player::play();
    animation::player<animation::move>::launch(animation::move(index_on, used_from_index, type));
    animation::base_player::play();
    board::give_back(entity_id, used_from_index);

    damage_dealers::standard_damage_dealer(damage, board::at(index_on), entity_id);

    used = true;
}