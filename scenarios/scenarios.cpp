#include <entities/samurai_rat.h>
#include <entities/troll.h>
#include <entities/droid.h>
#include "scenarios.h"
#include "core/game.h"
#include "abilities/damage_dealers.h"
#include "managers/entity_manager.h"
#include "entities/tree.h"
#include "entities/wolf.h"
#include "entities/shooter.h"
#include "entities/saurions_web.h"
#include "entities/native.h"
#include "entities/saurian.h"
#include "entities/saberhand.h"
#include "entities/stone.h"
#include "entities/saurions_web.h"
#include "utils/creator_helper.h"
#include "utils/scenario_helper.h"

std::unordered_map<std::string, std::function<void()>> scenarios_initializer;

void saurions_web_s(game& game) {

    auto shooter_id = entity_manager::create<shooter>();
    auto saberhand_id = entity_manager::create<saberhand>();
    auto saurion1_id = entity_manager::create<saurian>();
    auto saurion2_id = entity_manager::create<saurian>();
    auto saurion3_id = entity_manager::create<saurian>();
    auto saurion4_id = entity_manager::create<saurian>();

    auto ai_sequence = behavior_tree::helper::Sequence<ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy, ai::behavior_tree_tasks::find_nearest_enemy>::create();

    ai_manager::add_component(saurion1_id, ai_sequence);
    ai_manager::add_component(saurion2_id, ai_sequence);
    ai_manager::add_component(saurion3_id, ai_sequence);
    ai_manager::add_component(saurion4_id, ai_sequence);

    board::insert(board::to_index(2, 3), shooter_id);
    board::insert(board::to_index(2, 5), saberhand_id);

    board::insert(board::to_index(13, 4), saurion1_id);
    board::insert(board::to_index(12, 2), saurion2_id);
    board::insert(board::to_index(12, 6), saurion3_id);
    board::insert(board::to_index(4, 1), saurion4_id);

    players::create_human_player("tester");
    players::create_ai_player("enemy");
    players::add_entity_for_player("tester", shooter_id);
    players::add_entity_for_player("tester", saberhand_id);
    players::add_entity_for_player("enemy", saurion1_id);
    players::add_entity_for_player("enemy", saurion2_id);
    players::add_entity_for_player("enemy", saurion3_id);
    players::add_entity_for_player("enemy", saurion4_id);

    using creator_helper::pos;
    creator_helper::create_stones({ pos(5, 0), pos(5, 1), pos(9, 9), pos(1, 8), pos(14, 8) });

    auto native_id = entity_manager::create<native>();
    board::insert(board::to_index(12, 4), native_id);
    players::add_neutral_entity(native_id);

    auto saurion_web_id = entity_manager::create<saurions_web>();
    board::insert(board::to_index(12, 4), saurion_web_id);
    players::add_entity_for_player("enemy", saurion_web_id);

    auto callback = std::make_shared<std::function<void()>>([native_id]() {
        std::cout << "recaive damage\n";
        auto damage = healths_manager::receive_damage(native_id, 4);
        damage_dealers::play_change_health_animation(board::to_index(12, 4), damage);
    });

    auto web_poison_to_native = turn::turn_system::every_turn(callback);

    entity_remover::add_remover(saurion_web_id, [native_id, web_poison_to_native]() mutable {
        web_poison_to_native.reset();
        std::cout << "tester have native\n";
        players::add_entity_for_player("tester", native_id);
    });

    if_any_die({shooter_id, saberhand_id, native_id}, [&]() {
        std::cout << "defeat\n";
        game.defeat();
    });
    if_all_die({saurion1_id, saurion2_id, saurion3_id, saurion4_id}, [&]() {
        std::cout << "victory\n";
        game.victory();
    });
}

void wolves_dinner(game& game) {
    //auto shooter_id = entity_manager::create(entity_helper::turned_right(shooter::create()));
    auto samurai_id = entity_manager::create<samurai_rat>();
    //board::insert(board::to_index(2, 3), shooter_id);
    board::insert(board::to_index(2, 5), samurai_id);

    players::create_human_player("tester");
    players::create_ai_player("enemy");
    //players::add_entity_for_player("tester", shooter_id);
    players::add_entity_for_player("tester", samurai_id);

    auto ai_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_close_to,
            ai::behavior_tree_tasks::find_nearest_enemy
    >::create();

    using creator_helper::pos;
    std::vector<std::pair<std::size_t, std::size_t>> wolves_positions = {
            pos(5, 6),
            pos(9, 7),
            pos(12, 2),
            pos(12, 6),
            pos(8, 2)

    };
    std::vector<std::size_t> enemies_ids;
    for (auto&& wolf_pos : wolves_positions) {
        auto wolf_id = entity_manager::create<wolf>();
        ai_manager::add_component(wolf_id, ai_sequence);
        board::insert(board::to_index(wolf_pos.first, wolf_pos.second), wolf_id);
        players::add_entity_for_player("enemy", wolf_id);
        enemies_ids.push_back(wolf_id);
    }

    std::vector<std::pair<std::size_t, std::size_t>> trees_positions;
    for (int i = 0; i < board::cols_n; ++i) {
        for (int j = 0; j < board::rows_n; ++j) {
             if (i == 0 || j == 0 || i == board::cols_n - 1|| j == board::rows_n - 1) {
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
        game.defeat();
    });
    if_all_die(enemies_ids, [&]() {
        std::cout << "victory\n";
        game.victory();
    });
}

void skirmish(game& game) {

    auto shooter_id = entity_manager::create<shooter>();
    auto samurai_id = entity_manager::create<samurai_rat>();
    auto droid_id = entity_manager::create<droid>();

    board::insert(board::to_index(2, 3), shooter_id);
    board::insert(board::to_index(2, 5), samurai_id);
    board::insert(board::to_index(2, 7), droid_id);

    players::create_human_player("tester1");
    players::create_human_player("tester2");
    players::add_entity_for_player("tester1", shooter_id);
    players::add_entity_for_player("tester1", samurai_id);
    players::add_entity_for_player("tester1", droid_id);

    auto saberhand_id = entity_manager::create<saberhand>();
    auto native_id = entity_manager::create<native>();
    auto troll_id = entity_manager::create<troll>();
    board::insert(board::to_index(12, 3), saberhand_id);
    board::insert(board::to_index(12, 5), native_id);
    board::insert(board::to_index(12, 7), troll_id);

    players::add_entity_for_player("tester2", saberhand_id);
    players::add_entity_for_player("tester2", native_id);
    players::add_entity_for_player("tester2", troll_id);

//    auto ai_sequence = behavior_tree::helper::Sequence<
//            ai::behavior_tree_tasks::blackboard,
//            ai::behavior_tree_tasks::attack_enemy,
//            ai::behavior_tree_tasks::go_close_to,
//            ai::behavior_tree_tasks::find_nearest_enemy
//    >::create();

    using creator_helper::pos;
//    std::vector<std::pair<std::size_t, std::size_t>> wolves_positions = {
//            pos(5, 6),
//            pos(9, 7),
//            pos(12, 2),
//            pos(12, 6),
//            pos(8, 2)
//
//    };
//    std::vector<std::size_t> enemies_ids;
//    for (auto&& wolf_pos : wolves_positions) {
//        auto wolf_id = entity_manager::create(entity_helper::turned_left(wolf::create()));
//        ai_manager::add_component(wolf_id, ai_sequence);
//        board::insert(board::to_index(wolf_pos.first, wolf_pos.second), wolf_id);
//        players::add_entity_for_player("enemy", wolf_id);
//        enemies_ids.push_back(wolf_id);
//    }

    std::vector<std::pair<std::size_t, std::size_t>> trees_positions;
    for (int i = 0; i < board::cols_n; ++i) {
        for (int j = 0; j < board::rows_n; ++j) {
            if (i == 0 || j == 0 || i == board::cols_n - 1|| j == board::rows_n - 1) {
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

    if_all_die({shooter_id, samurai_id, droid_id}, [&]() {
        std::cout << "tester 2 win\n";
        game.defeat();
    });
    if_all_die({saberhand_id, native_id, troll_id}, [&]() {
        std::cout << "tester 1 win\n";
        game.victory();
    });
}

void create_scenario(game& game, const std::string& scenario_name) {
    skirmish(game);
}