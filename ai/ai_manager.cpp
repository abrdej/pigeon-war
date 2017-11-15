#include "ai_manager.h"
#include "core/states.h"
#include "core/board.h"

void ai_manager::perform_movement()
{
	for (auto& elem : map_)
	{
		auto entity_index = board::index_for(elem.first);
		states::state_controller::selected_index_ = entity_index;
		ai::behavior_tree_tasks::blackboard blackboard("enemy", entity_index);
		auto result = (*elem.second)(blackboard);
	}
}