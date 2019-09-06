#pragma once

#include <ai/behavior_node.h>

class ai_manager {
  std::unordered_map<std::uint32_t, ai::behavior_node_ptr> behavior_trees_;

  ai::ai_knowledge game_scope_knowledge_;

 public:
  void add_ai_for(std::uint32_t entity_id, ai::behavior_node_ptr behavior_tree);
  void perform_movement_new_ai(std::uint32_t player_id);

  ai::ai_knowledge& game_scope_knowledge();
  const ai::ai_knowledge& game_scope_knowledge() const;
};
