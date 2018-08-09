#include "battle_with_a_golem_scenario.h"

#include <ai/ai.h>
#include <ai/ai_manager.h>
#include <core/game.h>
#include <entities/golem.h>
#include <entities/saberhand.h>
#include <entities/shooter.h>

void scenarios::create_battle_with_a_golem_scenario() {

    game_board().set_size(15, 10);

    auto& entity_manager_ref = game::get<entity_manager>();
    auto& players_manager_ref = game::get<players_manager>();

    auto shooter_id = entity_manager_ref.create<shooter>();
    auto saberhand_id = entity_manager_ref.create<saberhand>();

    game_board().insert(game_board().to_index(2, 3), shooter_id);
    game_board().insert(game_board().to_index(2, 5), saberhand_id);

    auto tester_id = players_manager_ref.create_human_player("tester");
    auto enemy_id = players_manager_ref.create_ai_player("enemy");

    players_manager_ref.add_entity_for_player(tester_id, shooter_id);
    players_manager_ref.add_entity_for_player(tester_id, saberhand_id);

    auto best_aim_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_to,
            ai::behavior_tree_tasks::can_go_to,
            ai::behavior_tree_tasks::find_position_for_shot,
            ai::behavior_tree_tasks::find_best_aim_for_golem>::create();

    auto nearest_aim_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_to,
            ai::behavior_tree_tasks::find_position_for_shot,
            ai::behavior_tree_tasks::find_nearest_enemy>::create();

    auto ai_sequence = std::make_shared<behavior_tree::selector<ai::behavior_tree_tasks::blackboard>>();
    ai_sequence->add_task(best_aim_sequence);
    ai_sequence->add_task(nearest_aim_sequence);

    auto golem_id = entity_manager_ref.create<golem>();
    game::get<ai_manager>().add_ai_for(golem_id, ai_sequence);
    game_board().insert(game_board().to_index(10, 4), golem_id);
    players_manager_ref.add_entity_for_player(enemy_id, golem_id);
}