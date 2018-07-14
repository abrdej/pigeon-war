#include "ai.h"
#include "abilities/ability.h"
#include "managers/players_manager.h"
#include "core/board.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "core/game.h"
#include "abilities/abilities.h"
#include <random>
#include <thread>
#include <chrono>
#include <algorithm>
#include <managers/entity_manager.h>
#include <components/applied_effects.h>

namespace ai {

namespace behavior_tree_tasks {
using namespace behavior_tree;

bool find_nearest_enemy::operator()(blackboard &blackboard) {

    std::cout << "find_nearest_enemy\n";

    std::vector<std::uint32_t> enemies_indexes;
    players_funcs::enemy_entities_indexes(blackboard.entry<entry_tag::player_id>(), enemies_indexes);
    if (enemies_indexes.empty())
        return false;

    path_finder distance_finder(true);
    distance_finder.calc(blackboard.entry<entry_tag::my_entity_index_>());

    std::vector<std::uint32_t> distances_to_enemies;
    for (auto &enemy_index : enemies_indexes)
        distances_to_enemies.push_back(distance_finder.distance_to(enemy_index));

    auto min_it = std::min_element(std::begin(distances_to_enemies),
                                   std::end(distances_to_enemies));

    blackboard.entry<entry_tag::nearest_enemy_index>() = enemies_indexes[min_it - std::begin(distances_to_enemies)];

    return true;
}

bool attack_enemy::operator()(blackboard &blackboard) {

    std::cout << "attack_enemy\n";

    auto selected_index = states::state_controller::selected_index_;
    auto entity_id = game::get<board>().at(selected_index);
    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto offensive = abilities_ptr->of_type(ability_types::offensive);
    if (!offensive)
        return false;

    try_prepare_ability(*offensive, states::state_controller::selected_index_);
    auto can_attack = states::state_controller::is_possible_movement(blackboard.entry<entry_tag::nearest_enemy_index>());
    if (can_attack) {
        states::state_controller::do_action(blackboard.entry<entry_tag::nearest_enemy_index>());
    }

    return can_attack;
}

bool go_close_to::operator()(blackboard &blackboard) {

    std::cout << "go_close_to\n";

    auto entity_id = game::get<board>().at(blackboard.entry<entry_tag::my_entity_index_>());
    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto moving = abilities_ptr->of_type(ability_types::moving);
    if (!moving)
        return false;

    path_finder distance_finder(false);
    distance_finder.calc(blackboard.entry<entry_tag::my_entity_index_>());

    std::vector<std::uint32_t> neighbors;
    board_helper::neighboring_fields(blackboard.entry<entry_tag::nearest_enemy_index>(),
                                     neighbors, false);

    neighbors.erase(
            std::remove_if(std::begin(neighbors), std::end(neighbors), [&blackboard](std::uint32_t index) {
                return !game::get<board>().empty(index) && index != blackboard.entry<entry_tag::my_entity_index_>();
            }), std::end(neighbors));

    auto nearest_field = *std::min_element(std::begin(neighbors), std::end(neighbors),
                                           [&distance_finder](std::uint32_t first_elem,
                                                              std::uint32_t second_elem) {
                                               return distance_finder.distance_to(first_elem) <
                                                      distance_finder.distance_to(second_elem);
                                           });

    if (nearest_field == blackboard.entry<entry_tag::my_entity_index_>())
        return true;

    std::vector<std::uint32_t> path;
    distance_finder.path_to(nearest_field, path);

    try_prepare_ability(*moving, blackboard.entry<entry_tag::my_entity_index_>());
    for (auto &step : path) {
        if (states::state_controller::is_possible_movement(step)) {
            states::state_controller::do_action(step);
            return true;
        }
    }
    return false;
}

bool go_to::operator()(blackboard &blackboard) {

    std::cout << "go_to\n";

    auto entity_id = game::get<board>().at(blackboard.entry<entry_tag::my_entity_index_>());

    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto moving = abilities_ptr->of_type(ability_types::moving);
    if (!moving)
        return false;

    if (blackboard.entry<entry_tag::destination_index>() == blackboard.entry<entry_tag::my_entity_index_>())
        return true;

    path_finder path_finder(false);
    path_finder.calc(blackboard.entry<entry_tag::my_entity_index_>());

    std::vector<std::uint32_t> path;
    path_finder.path_to(blackboard.entry<entry_tag::destination_index>(), path);

    try_prepare_ability(*moving, blackboard.entry<entry_tag::my_entity_index_>());

    for (auto &step : path) {
        if (states::state_controller::is_possible_movement(step)) {
            states::state_controller::do_action(step);
            return true;
        }
    }
    return false;
}

bool can_go_to::operator()(blackboard &blackboard) {

    std::cout << "can_go_to\n";

    auto entity_id = game::get<board>().at(blackboard.entry<entry_tag::my_entity_index_>());

    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto moving = abilities_ptr->of_type(ability_types::moving);
    if (!moving)
        return false;

    if (blackboard.entry<entry_tag::destination_index>() == blackboard.entry<entry_tag::my_entity_index_>())
        return true;

    try_prepare_ability(*moving, blackboard.entry<entry_tag::my_entity_index_>());

    return states::state_controller::is_possible_movement(blackboard.entry<entry_tag::destination_index>());
}

bool find_position_for_shot::operator()(blackboard &blackboard) {

    std::cout << "find_position_for_shot\n";

    auto selected_index = states::state_controller::selected_index_;
    auto entity_id = game::get<board>().at(selected_index);
    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto offensive = abilities_ptr->of_type(ability_types::offensive);
    if (!offensive)
        return false;

    path_finder path_finder(false);

    auto destination_index = path_finder.find_first_satisfy_conditions(selected_index,
                                                                       [&offensive, &blackboard](
                                                                               std::uint32_t index) -> bool {
                                                                           try_prepare_ability(*offensive,
                                                                                               index);
                                                                           auto can_attack =
                                                                                   states::state_controller::is_possible_movement(
                                                                                           blackboard.entry<entry_tag::nearest_enemy_index>());
                                                                           return can_attack;
                                                                       });
    blackboard.entry<entry_tag::destination_index>() = destination_index;
    return destination_index != -1;
}

bool find_best_aim::operator()(blackboard &blackboard) {

    std::cout << "find_best_aim\n";

    std::vector<std::uint32_t> enemies_indexes;
    players_funcs::enemy_entities_indexes(blackboard.entry<entry_tag::player_id>(), enemies_indexes);
    if (enemies_indexes.empty())
        return false;

    std::int32_t min_health = std::numeric_limits<std::int32_t>::max();
    std::uint32_t min_health_enemy_index = 0;

    for (auto &&enemy_index : enemies_indexes) {
        auto enemy_id = game::get<board>().at(enemy_index);
        auto health = game::get<entity_manager>().get(enemy_id).get<health_field>()->health;

        if (health < min_health) {
            min_health = health;
            min_health_enemy_index = enemy_index;
        }
    }

    blackboard.entry<entry_tag::nearest_enemy_index>() = min_health_enemy_index;

    return true;
}

bool find_best_aim_for_golem::operator()(blackboard &blackboard) {

    std::cout << "find_best_aim_for_golem\n";

    std::vector<std::uint32_t> enemies_indexes;
    players_funcs::enemy_entities_indexes(blackboard.entry<entry_tag::player_id>(), enemies_indexes);

    if (enemies_indexes.empty())
        return false;

    std::int32_t min_health = std::numeric_limits<std::int32_t>::max();
    std::uint32_t min_health_enemy_index = 0;

    for (auto &&enemy_index : enemies_indexes) {
        auto enemy_id = game::get<board>().at(enemy_index);

        auto has_power_bullet_effect =
                game::get<entity_manager>().get(enemy_id).get<applied_effects>()->has("effect of a power bullet");

        if (!has_power_bullet_effect) {
            auto health = game::get<entity_manager>().get(enemy_id).get<health_field>()->health;
            if (health < min_health) {
                min_health = health;
                min_health_enemy_index = enemy_index;
            }
        }
    }

    blackboard.entry<entry_tag::nearest_enemy_index>() = min_health_enemy_index;

    return true;
}

}
}
