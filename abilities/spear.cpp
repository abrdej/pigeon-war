#include <core/states.h>
#include "spear.h"
#include "damage_dealers.h"

spear::spear(std::size_t id) : entity_id(id) {
    onEveryRound([this]() {
        used = false;
    });

    healths_manager::on_receive_damage(entity_id, [this](const damage_pack& dmg) mutable {
       accumulated_damage += 4;
    }, healths_manager::on_receive_damage_policy::after);
}

void spear::prepare(size_t for_index) {

    states::state_controller::selected_index_ = for_index;

    board_helper::calc_straight(for_index,
                                states::state_controller::possible_movements_,
                                states::state_controller::possible_movements_costs_,
                                range);

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });
}

void spear::use(size_t index_on) {

    if (used)
        return;

    used = true;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    play_animation(used_from_index, index_on);

    int full_damage = damage + accumulated_damage;

    damage_dealers::standard_damage_dealer(melee_damage(full_damage, board::at(index_on), entity_id));

    accumulated_damage = 0;
}

void spear::play_animation(size_t from_index, size_t to_index) {
    auto entity_id = board::take(from_index);
    animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "guardian_attack.png"));
    animation::base_player::play();
    animation::player<animation::move>::launch(animation::move(to_index, from_index, entity_id));
    animation::base_player::play();
    board::give_back(entity_id, from_index);
}
