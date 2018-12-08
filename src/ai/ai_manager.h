#pragma once

#include <memory>

#include <ai/ai.h>
#include <ai/behavior_tree.h>

class ai_manager {
	using BaseTask = behavior_tree::base_task<ai::behavior_tree_tasks::blackboard>;
	using BaseTaskPtr = std::shared_ptr<BaseTask>;
	std::unordered_map<std::uint32_t, BaseTaskPtr> behavior_trees;

public:
	void add_ai_for(std::uint32_t entity_id, BaseTaskPtr ai);
	void perform_movement(std::uint32_t for_player_of_id);
};
