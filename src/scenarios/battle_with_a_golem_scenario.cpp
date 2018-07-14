#include "battle_with_a_golem_scenario.h"
#include "core/game.h"

#include <entities/samurai_rat.h>
#include <ai/ai.h>
#include <ai/ai_manager.h>
#include <utils/creator_helper.h>
#include <entities/wolf.h>
#include <entities/stone.h>
#include <managers/managers.h>
#include <entities/tree.h>
#include <utils/scenario_helper.h>
#include <entities/shooter.h>
#include <entities/saurian.h>
#include <entities/saberhand.h>
#include <entities/native.h>
#include <entities/saurian_web.h>
#include <abilities/damage_dealers.h>
#include <entities/golem.h>

void create_battle_with_a_golem_scenario() {

    auto& entity_manager_ref = game::get<entity_manager>();
    auto& board_ref = game::get<board>();
    auto& players_manager_ref = game::get<players_manager>();

    auto shooter_id = entity_manager_ref.create<shooter>();
    auto saberhand_id = entity_manager_ref.create<saberhand>();

    board_ref.insert(board_ref.to_index(2, 3), shooter_id);
    board_ref.insert(board_ref.to_index(2, 5), saberhand_id);

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
    board_ref.insert(board_ref.to_index(10, 4), golem_id);
    players_manager_ref.add_entity_for_player(enemy_id, golem_id);
}