#include <core/states_controller.h>
#include <core/board.h>
#include <managers/players_manager.h>
#include <components/applied_effects.h>
#include <managers/entity_manager.h>
#include "assassin_slash.h"
#include "damage_dealers.h"

assassin_slash::assassin_slash(std::uint32_t entity_id) {

}

void assassin_slash::prepare(std::uint32_t for_index) {
    states::state_controller::selected_index_ = for_index;

    path_finder path_finder(true);
    path_finder.calc(for_index);

    std::vector<std::uint32_t> possible_fields;
    std::vector<std::uint32_t> costs;
    path_finder.get_possible_movements(possible_fields,
                                       costs,
                                       range);

    states::state_controller::possible_movements_.clear();

    for (auto&& field_index : possible_fields) {
        if (!game::get<board>().empty(field_index) && players_funcs::enemy_entity(field_index)) {
            auto enemy_id = game::get<board>().at(field_index);
            auto has_death_mark = has_effect(enemy_id, "death_mark");
            if (has_death_mark) {
                states::state_controller::possible_movements_.push_back(field_index);
            }
        }
    }

    states::state_controller::actual_targeting_type_ = target_types::enemy;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return set_landing(index);
                                              });
}

void assassin_slash::set_landing(std::uint32_t for_index) {

    marked_target_index = for_index;

    board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, true);

    if (states::state_controller::possible_movements_.empty()) {
        return;
    }

    states::state_controller::actual_targeting_type_ = target_types::moving;
    states::state_controller::wait_for_action([this](std::uint32_t index)
                                              {
                                                  return use(index);
                                              });

}

void assassin_slash::use(std::uint32_t index_on) {

    auto used_from_index = states::state_controller::selected_index_;

//    animations_queue::push_animation(animation_types::flash_bitmap, marked_target_index, 150, 0, "assassin_slash);

    auto entity_id = game::get<board>().take(used_from_index);
    game::get<board>().give_back(entity_id, index_on);

    states::state_controller::selected_index_ = index_on;

    play_animation(index_on, marked_target_index);

    auto enemy_id = game::get<board>().at(marked_target_index);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

    if (game::get<entity_manager>().alive(enemy_id)) {
        remove_effect(enemy_id, "death_mark");
    }
}

void assassin_slash::play_animation(std::uint32_t from_index, std::uint32_t to_index) {
    auto entity_id = game::get<board>().take(from_index);

//    animations_queue::push_animation(animation_types::move, from_index, to_index, entity_id, "none);
//    animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, "ninja_attack);
//    animations_queue::push_animation(animation_types::move, to_index, from_index, entity_id, "none);

    game::get<board>().give_back(entity_id, from_index);
}