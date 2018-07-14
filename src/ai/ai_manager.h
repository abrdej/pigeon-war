#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include <memory>
#include "managers/managers.h"
#include "ai.h"
#include "behavior_tree.h"

class ai_manager
{
	std::unordered_map<std::uint32_t, std::shared_ptr<behavior_tree::base_task<ai::behavior_tree_tasks::blackboard>>>
			behavior_trees;

public:
	void add_ai_for(std::uint32_t entity_id,
	std::shared_ptr<behavior_tree::base_task<ai::behavior_tree_tasks::blackboard>> ai);
	void perform_movement(std::uint32_t for_player_of_id);
};

#endif