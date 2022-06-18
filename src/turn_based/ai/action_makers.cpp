#include <turn_based/ai/action_makers.h>

#include <iostream>

#include <turn_based/abilities.h>
#include <turn_based/board.h>
#include <turn_based/logger.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>

namespace ai {
namespace nodes {

bool attack_enemy::operator()(ai_knowledge& knowledge) {
  LOG(debug) << "try run attack_enemy node";

  auto entity_id = active_entity_id(knowledge);
  auto entity_index = game_board().index_for(active_entity_id(knowledge));

  if (!knowledge.entity(entity_id).has("target_enemy_index")) {
    return false;
  }

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto offensive = abilities_ptr->of_type(ability_types::offensive);
  if (!offensive) return false;

  try_prepare_ability(*offensive, entity_index);

  auto target_enemy_index = knowledge.entity(entity_id).get<std::uint32_t>("target_enemy_index");

  if (game_control().is_possible_movement(target_enemy_index)) {
    game_control().do_action(target_enemy_index);
    return true;
  }

  return false;
}

}  // namespace nodes
}  // namespace ai
