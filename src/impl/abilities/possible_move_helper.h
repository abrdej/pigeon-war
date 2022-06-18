//
// Created by abrde on 20.12.2017.
//

#ifndef PIGEONWAR_POSSIBLE_MOVE_HELPER_H
#define PIGEONWAR_POSSIBLE_MOVE_HELPER_H

#include <turn_based/path_finder.h>
#include <turn_based/game_controller.h>
#include <turn_based/ability.h>

#define ENEMY target_types::enemy
#define MOVING target_types::moving

#define PATH_FINDER_PREPARE(TARGET_TYPE) \
void prepare(std::uint32_t for_index) override { \
states::state_controller::selected_index_ = for_index; \
    \
path_finder path_finder(true); \
path_finder.calc(for_index); \
path_finder.get_possible_movements(states::state_controller::possible_movements_, \
        states::state_controller::possible_movements_costs_, \
        range); \
\
states::state_controller::actual_targeting_type_ = TARGET_TYPE; \
states::state_controller::wait_for_action([this](std::uint32_t index) \
{ \
return use(index); \
}); \
} \


#define STRAIGHT_PREPARE(TARGET_TYPE) \
void prepare(std::uint32_t for_index) override { \
states::state_controller::selected_index_ = for_index; \
 \
board_helper::calc_straight(for_index, states::state_controller::possible_movements_, \
        states::state_controller::possible_movements_costs_, \
        range); \
 \
states::state_controller::actual_targeting_type_ = TARGET_TYPE; \
states::state_controller::wait_for_action([this](std::uint32_t index) \
{ \
return use(index); \
}); \
} \


#define STRAIGHT_PREPARE_ENEMY() \
STRAIGHT_PREPARE(target_types::enemy) \

#endif //PIGEONWAR_POSSIBLE_MOVE_HELPER_H
