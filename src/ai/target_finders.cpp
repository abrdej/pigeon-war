#include <ai/target_finders.h>

#include <iostream>
#include <boost/range/algorithm/min_element.hpp>

#include <abilities/abilities.h>
#include <components/applied_effects.h>
#include <core/board.h>
#include <core/game_controller.h>

namespace ai {
namespace nodes {

bool find_nearest_enemy::operator()(ai_knowledge& knowledge) {

    std::cout << "try run find_nearest_enemy node\n";

    auto player_id = active_player_id(knowledge);

    std::vector<std::uint32_t> enemies_indexes;
    players_helpers::enemy_entities_indexes(player_id, enemies_indexes);
    if (enemies_indexes.empty())
        return false;

    auto entity_index = active_entity_index(knowledge);

    path_finder distance_finder(true);
    distance_finder.calc(entity_index);

    std::vector<std::int32_t> distances_to_enemies;
    for (auto enemy_index : enemies_indexes)
        distances_to_enemies.push_back(distance_finder.distance_to(enemy_index));

    auto entity_id = active_entity_id(knowledge);

    auto min_it = boost::range::min_element(distances_to_enemies);
    std::uint32_t nearest_enemy_index = enemies_indexes[min_it - std::begin(distances_to_enemies)];

    knowledge.entity(entity_id).insert("nearest_enemy_index", nearest_enemy_index);
    knowledge.entity(entity_id).insert("target_enemy_index", nearest_enemy_index);

    return true;
}

bool find_position_for_shot::operator()(ai_knowledge& knowledge) {

    std::cout << "try run find_position_for_shot node\n";

    auto entity_index = active_entity_index(knowledge);
    auto entity_id = active_entity_id(knowledge);

    if (!knowledge.entity(entity_id).has("target_enemy_index")) {
        return false;
    }

    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto offensive_ability = abilities_ptr->of_type(ability_types::offensive);
    if (!offensive_ability)
        return false;

    path_finder path_finder(false);

    auto destination_index =
            path_finder.find_first_satisfy_conditions(entity_index,
                                                      [&offensive_ability, &knowledge, entity_id]
                                                              (std::uint32_t index) -> bool {
                                                          try_prepare_ability(*offensive_ability, index);
                                                          return game_control().is_possible_movement(
                                                                          knowledge.entity(
                                                                                  entity_id).get<std::uint32_t>(
                                                                                  "target_enemy_index"));
                                                      });

    if (destination_index == no_selected_index) {
        return false;
    }

    knowledge.entity(entity_id).insert("destination_index", destination_index);
    return true;
}

bool find_lowest_health_target::operator()(ai_knowledge& knowledge) {

    std::cout << "try run find_lowest_health_target node\n";

    auto player_id = active_player_id(knowledge);
    auto entity_id = active_entity_id(knowledge);

    std::vector<std::uint32_t> enemies_indexes;
    players_helpers::enemy_entities_indexes(player_id, enemies_indexes);
    if (enemies_indexes.empty())
        return false;

    std::int32_t lowest_health = std::numeric_limits<std::int32_t>::max();
    std::uint32_t lowest_health_enemy_index = 0;

    for (auto enemy_index : enemies_indexes) {
        auto enemy_id = game_board().at(enemy_index);
        auto health = game::get<entity_manager>().get(enemy_id).get<health_field>()->health;

        if (health < lowest_health) {
            lowest_health = health;
            lowest_health_enemy_index = enemy_index;
        }
    }

    knowledge.player(player_id).insert("lowest_health_target_index", lowest_health_enemy_index);
    knowledge.entity(entity_id).insert("target_enemy_index", lowest_health_enemy_index);

    return true;
}

bool find_best_target_for_golem::operator()(ai_knowledge& knowledge) {

    std::cout << "try run find_best_target_for_golem node\n";

    auto player_id = active_player_id(knowledge);
    auto entity_id = active_entity_id(knowledge);

    std::vector<std::uint32_t> enemies_indexes;
    players_helpers::enemy_entities_indexes(player_id, enemies_indexes);

    if (enemies_indexes.empty())
        return false;

    std::int32_t lowest_health = std::numeric_limits<std::int32_t>::max();
    std::uint32_t best_target_index = std::numeric_limits<std::uint32_t>::max();

    for (auto enemy_index : enemies_indexes) {
        auto enemy_id = game_board().at(enemy_index);

        auto has_power_bullet_effect =
                game::get<entity_manager>().get(enemy_id).get<applied_effects>()->has("effect of a power bullet");

        if (!has_power_bullet_effect) {
            auto health = game::get<entity_manager>().get(enemy_id).get<health_field>()->health;
            if (health < lowest_health) {
                lowest_health = health;
                best_target_index = enemy_index;
            }
        }
    }

    if (best_target_index == std::numeric_limits<std::uint32_t>::max()) {
        return false;
    }

    knowledge.entity(entity_id).insert("target_enemy_index", best_target_index);

    return true;
}

} // namespace nodes
} // namespace ai
