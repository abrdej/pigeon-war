#include "wolves_dinner.h"

#include <ai/ai.h>
#include <ai/ai_manager.h>
#include <core/game_controller.h>
#include <entities/tree.h>
#include <entities/samurai_rat.h>
#include <entities/stone.h>
#include <entities/wolf.h>
#include <scenarios/creator_helper.h>
#include <scenarios/scenario_helper.h>


void create_wolves_dinner() {

    game_board().set_size(15, 10);

    auto& players_manager_ref = game_get<players_manager>();

    //auto shooter_id = entity_manager::create(entity_helper::turned_right(shooter::create()));
    auto samurai_id = game::get<entity_manager>().create<samurai_rat>();
    //board::insert(board::to_index(2, 3), shooter_id);
    game_board().insert(game_board().to_index(2, 5), samurai_id);

    auto tester_id = players_manager_ref.create_human_player("tester");
    auto enemy_id = players_manager_ref.create_ai_player("enemy");
    //players::add_entity_for_player("tester", shooter_id);
    players_manager_ref.add_entity_for_player(tester_id, samurai_id);

    auto ai_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_close_to,
            ai::behavior_tree_tasks::find_nearest_enemy
    >::create();

    using creator_helper::pos;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> wolves_positions = {
            pos(5, 6),
            pos(9, 7),
            pos(12, 2),
            pos(12, 6),
            pos(8, 2)
    };
    std::vector<std::uint32_t> enemies_ids;
    for (auto&& wolf_pos : wolves_positions) {
        auto wolf_id = game::get<entity_manager>().create<wolf>();
        game::get<ai_manager>().add_ai_for(wolf_id, ai_sequence);
        game_board().insert(game_board().to_index(wolf_pos.first, wolf_pos.second), wolf_id);
        players_manager_ref.add_entity_for_player(enemy_id, wolf_id);
        enemies_ids.push_back(wolf_id);
    }

    std::vector<std::pair<std::uint32_t, std::uint32_t>> trees_positions;
    for (std::int32_t i = 0; i < game_board().cols_n; ++i) {
        for (std::int32_t j = 0; j < game_board().rows_n; ++j) {
            if (i == 0 || j == 0 || i == game_board().cols_n - 1|| j == game_board().rows_n - 1) {
                trees_positions.push_back(pos(i, j));
            }
        }
    }
    creator_helper::create_neutral_many<tree>(trees_positions);
    creator_helper::create_neutral_many<tree>({pos(7, 1), pos(8, 1), pos(9, 1), pos(9, 2)});
    creator_helper::create_neutral_many<tree>({pos(8, 8), pos(9, 8), pos(8, 6), pos(9, 6),
                                               pos(10, 8), pos(11, 8), pos(10, 7), pos(11, 7)});
    creator_helper::create_neutral_many<tree>({pos(4, 4), pos(5, 4), pos(4, 5), pos(4, 6)});
    creator_helper::create_neutral_many<stone>({pos(1, 1), pos(5, 5)});

    if_any_die({samurai_id}, [&]() {
        std::cout << "defeat\n";
        game_control().defeat();
    });
    if_all_die(enemies_ids, [&]() {
        std::cout << "victory\n";
        game_control().victory(tester_id);
    });
}
