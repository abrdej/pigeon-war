#include <ai/ai_manager.h>

#include <core/board.h>
#include <core/game_controller.h>

void ai_manager::add_ai_for(std::uint32_t entity_id, ai::behavior_node_ptr behavior_tree) {
    behavior_trees_.emplace(entity_id, behavior_tree);
    game::get<entity_manager>().on_destroy(entity_id, [this, entity_id]() {
        behavior_trees_.erase(entity_id);
    });
}

void ai_manager::perform_movement_new_ai(std::uint32_t player_id) {
    auto temp_behavior_trees = behavior_trees_;

    for (auto behavior_tree_entry : temp_behavior_trees) {

        auto entity_id = behavior_tree_entry.first;

        ai::ai_knowledge turn_scope_knowledge;
        turn_scope_knowledge.global().insert("active_player_id", player_id);
        turn_scope_knowledge.global().insert("active_entity_id", entity_id);

        auto behavior_tree = behavior_tree_entry.second;
        (void)(*behavior_tree)(turn_scope_knowledge);
    }
}

ai::ai_knowledge& ai_manager::game_scope_knowledge() {
    return game_scope_knowledge_;
}

const ai::ai_knowledge& ai_manager::game_scope_knowledge() const {
    return game_scope_knowledge_;
}
