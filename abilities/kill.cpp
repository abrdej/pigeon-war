#include <core/states.h>
#include <core/board.h>
#include <core/players.h>
#include <managers/additions_manager.h>
#include <managers/entity_manager.h>
#include "kill.h"
#include "damage_dealers.h"

kill::kill() {

}

void kill::prepare(size_t for_index) {
    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);

    std::vector<std::size_t> possible_fields;
    std::vector<std::size_t> costs;
    path_finder.get_possible_movements(states::state_controller::possible_movements_,
                                       costs,
                                       range);

//    states::state_controller::possible_movements_.clear();
//
//    for (auto&& field_index : possible_fields) {
//        if (!board::empty(field_index) && players_funcs::enemy_entity(field_index)) {
//            auto enemy_id = board::at(field_index);
//            auto healths_pack = healths_manager::component_for(enemy_id);
//            if (healths_pack.health <= max_health) {
//                states::state_controller::possible_movements_.push_back(field_index);
//            }
//        }
//    }

    states::state_controller::actual_targeting_type_ = states::target_types::enemy;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return set_landing(index);
                                              });
}

void kill::set_landing(size_t for_index) {

    target_index = for_index;

    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, true);

    if (states::state_controller::possible_movements_.empty()) {
        return;
    }

    states::state_controller::actual_targeting_type_ = states::target_types::moving;
    states::state_controller::wait_for_action([this](size_t index)
                                              {
                                                  return use(index);
                                              });

}

void kill::use(size_t index_on) {

    auto used_from_index = states::state_controller::selected_index_;

    auto entity_id = board::take(used_from_index);

    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "killer_jump.png"));
    animation::base_player::play();

    board::give_back(entity_id, index_on);

    states::state_controller::selected_index_ = index_on;

    play_animation(index_on, target_index);

    auto enemy_id = board::at(target_index);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));


}

void kill::play_animation(size_t from_index, size_t to_index) {
    auto entity_id = board::take(from_index);
    animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "killer_attack.png"));
    animation::base_player::play();
    animation::player<animation::move>::launch(animation::move(to_index, from_index, entity_id));
    animation::base_player::play();
    board::give_back(entity_id, from_index);
}