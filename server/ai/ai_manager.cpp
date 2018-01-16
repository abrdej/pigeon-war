#include "ai_manager.h"
#include "core/states_controller.h"
#include "core/board.h"

void ai_manager::perform_movement(std::uint32_t for_player_of_id)
{
	for (auto& elem : map_)
	{
		auto entity_index = board::index_for(elem.first);
		states::state_controller::selected_index_ = entity_index;
		ai::behavior_tree_tasks::blackboard blackboard(for_player_of_id, entity_index);
		auto result = (*elem.second)(blackboard);
	}
}