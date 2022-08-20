#include <turn_based/ai/ai_manager.h>

#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/game_controller.h>

void ai_manager::add_ai_for(entity_id_t entity_id, ai::behavior_node_ptr behavior_tree) {
  behavior_trees_.emplace(entity_id, std::move(behavior_tree));
  game::get<entity_manager>().on_destroy(entity_id,
                                         [this, entity_id]() { behavior_trees_.erase(entity_id); });
}

void ai_manager::perform_movement_new_ai(player_id_t player_id) {
  auto temp_behavior_trees = behavior_trees_;

  for (auto& behavior_tree_entry : temp_behavior_trees) {
    auto entity_id = behavior_tree_entry.first;

    ai::ai_knowledge turn_scope_knowledge;
    turn_scope_knowledge.global().insert("active_player_id", player_id);
    turn_scope_knowledge.global().insert("active_entity_id", entity_id);

    auto behavior_tree = behavior_tree_entry.second;
    (*behavior_tree)(turn_scope_knowledge);
  }
}
