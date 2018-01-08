#include <server/core/states_controller.h>
#include <core/board.h>
#include <managers/players_manager.h>
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

    bool is_killer_instinct_active = additions_manager::has_component(entity_id, "killer_instinct");

    animations_queue::push_animation(animation_types::hide_show, used_from_index, 0, 0, bitmap_key::none);
    animations_queue::push_animation(animation_types::flash_bitmap, index_on, 150, -1, bitmap_key::killer_jump);
    animations_queue::push_animation(animation_types::hide_show, index_on, 1, entity_id, bitmap_key::none);

    board::give_back(entity_id, index_on);

    states::state_controller::selected_index_ = index_on;

    play_animation(index_on, target_index);

    auto enemy_id = board::at(target_index);

    damage_dealers::standard_damage_dealer(melee_damage(is_killer_instinct_active ? damage_with_killer_instinct : damage, enemy_id, entity_id));
}

void kill::play_animation(size_t from_index, size_t to_index) {
    auto entity_id = board::take(from_index);

    animations_queue::push_animation(animation_types::move, from_index, to_index, entity_id, bitmap_key::none);
    animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, -1, bitmap_key::killer_attack);
    animations_queue::push_animation(animation_types::move, to_index, from_index, entity_id, bitmap_key::none);

    board::give_back(entity_id, from_index);
}