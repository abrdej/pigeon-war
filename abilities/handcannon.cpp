#include <core/states.h>
#include "handcannon.h"
#include "damage_dealers.h"

handcannon::handcannon() {
    onEveryRound([this]() {
        used = false;
    });
}

void handcannon::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void handcannon::use(size_t index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    used = true;
}

void handcannon::play_animation(size_t from_index, size_t to_index) {
    animation::base_player::play();
    animation::player<animation::move>::launch
            (animation::move(from_index, to_index, typeid(*this)));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch
            (animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "handcannonbum.png"));
    animation::base_player::play();
}
