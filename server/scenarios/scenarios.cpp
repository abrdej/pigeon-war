#include <entities/samurai_rat.h>
#include <entities/troll.h>
#include <entities/mouse.h>
#include <entities/droid.h>
#include <entities/werewolf.h>
#include <entities/grenadier.h>
#include <entities/destroyer.h>
#include <entities/golem.h>
#include "scenarios.h"
#include "core/game.h"
#include "server/abilities/damage_dealers.h"
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
#include "entities/warrior.h"
#include "utils/creator_helper.h"
#include "utils/scenario_helper.h"
#include "ai/behavior_tree.h"
#include "ai/ai_manager.h"

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

    auto tester_id = players_manager::create_human_player("tester");
    auto enemy_id = players_manager::create_ai_player("enemy");
    players_manager::add_entity_for_player(tester_id, shooter_id);
    players_manager::add_entity_for_player(tester_id, saberhand_id);
    players_manager::add_entity_for_player(enemy_id, saurion1_id);
    players_manager::add_entity_for_player(enemy_id, saurion2_id);
    players_manager::add_entity_for_player(enemy_id, saurion3_id);
    players_manager::add_entity_for_player(enemy_id, saurion4_id);

    using creator_helper::pos;
    creator_helper::create_stones({ pos(5, 0), pos(5, 1), pos(9, 9), pos(1, 8), pos(14, 8) });

    auto native_id = entity_manager::create<native>();
    board::insert(board::to_index(12, 4), native_id);
    players_manager::add_neutral_entity(native_id);

    auto saurion_web_id = entity_manager::create<saurions_web>();
    board::insert(board::to_index(12, 4), saurion_web_id);
    players_manager::add_entity_for_player(enemy_id, saurion_web_id);

//    auto web_poison_to_native = turn::turn_system::every_round([native_id]() {
//        std::cout << "receive damage\n";
//        auto damage = healths_manager::receive_damage(damage_pack(4, damage_types::UNDEFINED, native_id));
////        damage_dealers::play_change_health_animation(board::to_index(12, 4), damage);
//    });

//    entity_remover::add_remover(saurion_web_id, [tester_id, native_id, web_poison_to_native]() mutable {
//        web_poison_to_native.reset();
//        std::cout << "tester have native\n";
//        players_manager::add_entity_for_player(tester_id, native_id);
//    });

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

    auto tester_id = players_manager::create_human_player("tester");
    auto enemy_id = players_manager::create_ai_player("enemy");
    //players::add_entity_for_player("tester", shooter_id);
    players_manager::add_entity_for_player(tester_id, samurai_id);

    auto ai_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_close_to,
            ai::behavior_tree_tasks::find_nearest_enemy
    >::create();

    using creator_helper::pos;
    std::vector<std::pair<std::uint64_t, std::uint64_t>> wolves_positions = {
            pos(5, 6),
            pos(9, 7),
            pos(12, 2),
            pos(12, 6),
            pos(8, 2)

    };
    std::vector<std::uint64_t> enemies_ids;
    for (auto&& wolf_pos : wolves_positions) {
        auto wolf_id = entity_manager::create<wolf>();
        ai_manager::add_component(wolf_id, ai_sequence);
        board::insert(board::to_index(wolf_pos.first, wolf_pos.second), wolf_id);
        players_manager::add_entity_for_player(enemy_id, wolf_id);
        enemies_ids.push_back(wolf_id);
    }

    std::vector<std::pair<std::uint64_t, std::uint64_t>> trees_positions;
    for (std::int32_t i = 0; i < board::cols_n; ++i) {
        for (std::int32_t j = 0; j < board::rows_n; ++j) {
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

void battle_with_a_golem(game& game) {

    auto shooter_id = entity_manager::create<shooter>();
    auto saberhand_id = entity_manager::create<saberhand>();

    board::insert(board::to_index(2, 3), shooter_id);
    board::insert(board::to_index(2, 5), saberhand_id);

    auto tester_id = players_manager::create_human_player("tester");
    auto enemy_id = players_manager::create_ai_player("enemy");

    players_manager::add_entity_for_player(tester_id, shooter_id);
    players_manager::add_entity_for_player(tester_id, saberhand_id);

    auto best_aim_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_to,
            ai::behavior_tree_tasks::can_go_to,
            ai::behavior_tree_tasks::find_position_for_shot,
            ai::behavior_tree_tasks::find_best_aim>::create();

    auto nearest_aim_sequence = behavior_tree::helper::Sequence<
            ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy,
            ai::behavior_tree_tasks::go_to,
            ai::behavior_tree_tasks::find_position_for_shot,
            ai::behavior_tree_tasks::find_nearest_enemy>::create();

    auto ai_sequence = std::make_shared<behavior_tree::selector<ai::behavior_tree_tasks::blackboard>>();
    ai_sequence->add_task(best_aim_sequence);
    ai_sequence->add_task(nearest_aim_sequence);

    auto golem_id = entity_manager::create<golem>();
    ai_manager::add_component(golem_id, ai_sequence);
    board::insert(board::to_index(10, 4), golem_id);
    players_manager::add_entity_for_player(enemy_id, golem_id);
}


//#include <boost/fusion/container/vector.hpp>
//#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <core/states_controller.h>
#include <entities/treant.h>
#include <entities/fire.h>
#include <entities/thrower.h>
#include <entities/guardian.h>
#include <entities/creature.h>
#include <entities/handthrower.h>
#include <entities/robot.h>
#include <entities/spider.h>
#include <entities/sniper.h>
#include <entities/monk.h>
#include <entities/ninja.h>
#include <entities/absorber.h>
#include <entities/water.h>
#include <entities/wall.h>
#include <entities/fir.h>
#include <entities/wretch.h>
#include <entities/killer.h>
#include <entities/giant.h>
#include <entities/golem.h>
#include <entities/sorcerer.h>

//using Entites = boost::fusion::vector<shooter,
using Entites = std::tuple<shooter,
        destroyer,
        samurai_rat,
        droid,
        saberhand,
        native,
        troll,
        sniper,
        mouse,
        //werewolf,
        robot,
        monk,
        grenadier,
        ninja,
        //treant,
        thrower,
        killer,
        absorber,
        //saurian,
        giant,
        guardian,
        sorcerer,
        creature,
        wretch,
        warrior,
        handthrower,
        golem,
        spider>;

struct OwnerCallback {
    turn::turn_system::strong_receiver owner;
};

void create_trees_1() {
    using creator_helper::pos;
    creator_helper::create_neutral_many<tree>({pos(8, 1), pos(9, 1), pos(10, 1), pos(10, 2)});
    creator_helper::create_neutral_many<tree>({pos(10, 7), pos(11, 7), pos(10, 8), pos(11, 8)});
    creator_helper::create_neutral_many<tree>({pos(3, 1), pos(3, 2), pos(4, 1), pos(4, 2), pos(3, 5), pos(3, 6)});
    creator_helper::create_neutral_many<tree>({pos(5, 8), pos(6, 8)});
    creator_helper::create_neutral_many<stone>({pos(1, 1), pos(4, 5)});
}

template <typename Tuple, typename F, size_t ...Indices>
void for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
    using swallow = int[];
    (void)swallow{1,
                  (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
    };
}

template <typename Tuple, typename F>
void for_each(Tuple&& tuple, F&& f) {
    constexpr size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    for_each_impl(std::forward<Tuple>(tuple), std::forward<F>(f),
                  std::make_index_sequence<N>{});
}

void skirmish(game& game) {

    using creator_helper::pos;

    //creator_helper::create_neutral_many<fire>({pos(7, 4)});

    std::vector<std::pair<std::uint64_t, std::uint64_t>> trees_positions;
    for (std::int32_t i = 0; i < board::cols_n; ++i) {
        for (std::int32_t j = 0; j < board::rows_n; ++j) {
            if (i == 0 || j == 0 || i == board::cols_n - 1|| j == board::rows_n - 1) {
                trees_positions.push_back(pos(i, j));
            }
        }
    }

    create_trees_1();
    creator_helper::create_neutral_many<tree>(trees_positions);

//    creator_helper::create_neutral_many<fir>({pos(6, 1), pos(7, 1), pos(6, 2), pos(7, 2)});
//    creator_helper::create_neutral_many<fir>({pos(10, 1), pos(11, 1), pos(10, 2), pos(11, 2)});
//    creator_helper::create_neutral_many<fir>({pos(7, 7), pos(8, 7), pos(7, 8), pos(8, 8)});
//    creator_helper::create_neutral_many<fir>({pos(3, 7), pos(4, 7), pos(3, 8), pos(4, 8)});


//    creator_helper::create_neutral_many<wall>({pos(4, 4), pos(4, 5)});
//    creator_helper::create_neutral_many<wall>({pos(10, 5), pos(10, 6)});

//    creator_helper::create_neutral_many<fir>({pos(6, 4), pos(7, 4), pos(6, 5), pos(7, 5)});



    std::vector<std::pair<std::uint64_t, std::uint64_t>> init_positions = {
            pos(5, 2),
            pos(6, 2),
            pos(7, 2),
            pos(8, 2),
            pos(9, 2),

            pos(5, 3),
            pos(6, 3),
            pos(7, 3),
            pos(8, 3),
            pos(9, 3),

            pos(5, 4),
            pos(6, 4),
            pos(7, 4),
            pos(8, 4),
            pos(9, 4),

            pos(5, 5),
            pos(6, 5),
            pos(7, 5),
            pos(8, 5),
            pos(9, 5),

            pos(5, 6),
            pos(6, 6),
            pos(7, 6),
            pos(8, 6),
            pos(9, 6)
    };

    std::array<std::pair<std::uint64_t, std::uint64_t>, 8> positions = {
            pos(2, 2),
            pos(12, 2),
            pos(2, 4),
            pos(12, 4),
            pos(2, 6),
            pos(12, 6),
            pos(2, 8),
            pos(12, 8)
    };

    std::array<std::uint64_t, 2> players;
    for (auto& player : players) {
        player = players_manager::create_human_player();
    }

    std::uint64_t i = 0;

    std::unordered_set<std::uint64_t> entities_to_choose;

    auto init_entity = [&](auto x) {
        using EntityType = decltype(x);
        auto id = entity_manager::create<EntityType>();

        auto pos = init_positions[i++];
        board::insert(board::to_index(pos.first, pos.second), id);
        players_manager::add_neutral_entity(id);

        entities_to_choose.insert(id);
    };

//    std::int32_t tab[] = {(init_entity(std::forward<Args>(args)), 0)...};

    for_each(Entites{}, init_entity);

//
//boost::fusion::for_each(Entites{}, init_entity);

//    boost::fusion::for_each(Entites{}, [&i, &entities_to_choose, &init_positions](auto x) {
//        using EntityType = decltype(x);
//        auto id = entity_manager::create<EntityType>();
//
//        auto pos = init_positions[i++];
//        board::insert(board::to_index(pos.first, pos.second), id);
//        players_manager::add_neutral_entity(id);
//
//        entities_to_choose.insert(id);
//    });

    std::int32_t entities_for_player = 4;
    std::int32_t selections = 0;

    std::shared_ptr<OwnerCallback> holder = std::make_shared<OwnerCallback>();

    auto create_entities_container = [](){
        return std::unordered_map<std::uint64_t, std::vector<std::uint64_t>>();
    };

    auto add_entity_for_player = turn::turn_system::every_turn([=, entities = create_entities_container()]() mutable {

        auto entity_id = board::take(states::state_controller::selected_index_);

        entities[players[selections % 2]].push_back(entity_id);

        auto pos = positions[selections];
        auto new_index = board::to_index(pos.first, pos.second);
        board::give_back(entity_id, new_index);
        states::state_controller::selected_index_ = new_index;

        entities_to_choose.erase(entity_id);

        ++selections;

        if (selections == entities_for_player * 2) {

            for (auto&& entity_to_remove : entities_to_choose) {
                entity_manager::destroy(entity_to_remove);
            }

            for (auto&& player_pack : entities) {
                for (auto&& id : player_pack.second) {
                    players_manager::add_entity_for_player(player_pack.first, id);
                }
            }
            for (auto&& player_pack : entities) {
                if_all_die(player_pack.second, [&]() {
                    std::cout << player_pack.first << " win!!!\n";
                    game.defeat();
                });
            }

            entities.clear();

            holder.reset();
        }

    });

    holder->owner = add_entity_for_player;
}

void create_scenario(game& game, const std::string& scenario_name) {
    skirmish(game);
}
