#include <ai/ai_manager.h>

#include <core/board.h>
#include <core/game_controller.h>

void ai_manager::add_ai_for(std::uint32_t entity_id, BaseTaskPtr ai) {
	behavior_trees.emplace(entity_id, ai);
	game::get<entity_manager>().on_destroy(entity_id, [this, entity_id]() {
		behavior_trees.erase(entity_id);
	});
}

void ai_manager::perform_movement(std::uint32_t for_player_of_id)
{
	auto behavior_trees_copy = behavior_trees;
	for (auto& behavior_tree_entry : behavior_trees_copy) {

		std::cout << "perform movement\n";

		auto entity_index = game_board().index_for(behavior_tree_entry.first);
		game_control().selected_index_ = entity_index;
        using namespace ai::behavior_tree_tasks;
		blackboard blackboard;
        blackboard.set_entry<entry_tag::player_id>(for_player_of_id);
        blackboard.set_entry<entry_tag::my_entity_index_>(entity_index);
		/*auto result =*/ (*behavior_tree_entry.second)(blackboard);
	}
}
