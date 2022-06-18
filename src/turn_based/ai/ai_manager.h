#pragma once

#include <turn_based/ai/behavior_node.h>

class ai_manager {
 public:
  void add_ai_for(id_t entity_id, ai::behavior_node_ptr behavior_tree);
  void perform_movement_new_ai(id_t player_id);

  ai::ai_knowledge& game_scope_knowledge() {
    return game_scope_knowledge_;
  }
  const ai::ai_knowledge& game_scope_knowledge() const {
    return game_scope_knowledge_;
  }

 private:
  std::unordered_map<id_t, ai::behavior_node_ptr> behavior_trees_;
  ai::ai_knowledge game_scope_knowledge_;
};
