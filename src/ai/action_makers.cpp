#include <ai/action_makers.h>

#include <iostream>

#include <abilities/abilities.h>
#include <core/board.h>
#include <core/game_controller.h>

namespace ai {
namespace nodes {

bool attack_enemy::operator()(ai_knowledge& knowledge) {

    std::cout << "try run attack_enemy node\n";

    auto entity_id = active_entity_id(knowledge);
    auto entity_index = active_entity_index(knowledge);

    if (!knowledge.entity(entity_id).has("target_enemy_index")) {
        return false;
    }

    auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
    auto offensive = abilities_ptr->of_type(ability_types::offensive);
    if (!offensive)
        return false;

    try_prepare_ability(*offensive, entity_index);

    auto target_enemy_index = knowledge.entity(entity_id).get<std::uint32_t>("target_enemy_index");

    if (game_control().is_possible_movement(target_enemy_index)) {
        game_control().do_action(target_enemy_index);
        return true;
    }

    return false;
}

} // namespace nodes
} // namespace ai
