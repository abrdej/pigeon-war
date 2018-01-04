#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include <memory>
#include "common/managers.h"
#include "ai.h"
#include "behavior_tree.h"
struct ai_component;

class ai_manager : public base_manager<std::shared_ptr<behavior_tree::base_task<ai::behavior_tree_tasks::blackboard>>,
	std::shared_ptr<behavior_tree::base_task<ai::behavior_tree_tasks::blackboard>>>
{
public:
	static void perform_movement();
};

#endif