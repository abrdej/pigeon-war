#include "saurian_web_scenario.h"
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

void create_saurian_web(game &game) {

    auto &board_ref = game::get<board>();
    auto &entity_manager_ref = game::get<entity_manager>();
    auto &players_manager_ref = game::get<players_manager>();

    auto shooter_id = entity_manager_ref.create<shooter>();
    auto saberhand_id = entity_manager_ref.create<saberhand>();
    auto saurion1_id = entity_manager_ref.create<saurian>();
    auto saurion2_id = entity_manager_ref.create<saurian>();
    auto saurion3_id = entity_manager_ref.create<saurian>();
    auto saurion4_id = entity_manager_ref.create<saurian>();

    auto ai_sequence = behavior_tree::helper::Sequence<ai::behavior_tree_tasks::blackboard,
            ai::behavior_tree_tasks::attack_enemy, ai::behavior_tree_tasks::find_nearest_enemy>::create();

    game::get<ai_manager>().add_ai_for(saurion1_id, ai_sequence);
    game::get<ai_manager>().add_ai_for(saurion2_id, ai_sequence);
    game::get<ai_manager>().add_ai_for(saurion3_id, ai_sequence);
    game::get<ai_manager>().add_ai_for(saurion4_id, ai_sequence);

    board_ref.insert(board_ref.to_index(2, 3), shooter_id);
    board_ref.insert(board_ref.to_index(2, 5), saberhand_id);

    board_ref.insert(board_ref.to_index(13, 4), saurion1_id);
    board_ref.insert(board_ref.to_index(12, 2), saurion2_id);
    board_ref.insert(board_ref.to_index(12, 6), saurion3_id);
    board_ref.insert(board_ref.to_index(4, 1), saurion4_id);

    auto tester_id = players_manager_ref.create_human_player("tester");
    auto enemy_id = players_manager_ref.create_ai_player("enemy");
    players_manager_ref.add_entity_for_player(tester_id, shooter_id);
    players_manager_ref.add_entity_for_player(tester_id, saberhand_id);
    players_manager_ref.add_entity_for_player(enemy_id, saurion1_id);
    players_manager_ref.add_entity_for_player(enemy_id, saurion2_id);
    players_manager_ref.add_entity_for_player(enemy_id, saurion3_id);
    players_manager_ref.add_entity_for_player(enemy_id, saurion4_id);

    using creator_helper::pos;
    creator_helper::create_stones({pos(5, 0), pos(5, 1), pos(9, 9), pos(1, 8), pos(14, 8)});

    auto native_id = entity_manager_ref.create<native>();
    board_ref.insert(board_ref.to_index(12, 4), native_id);
    players_manager_ref.add_neutral_entity(native_id);

    auto saurion_web_id = entity_manager_ref.create<saurian_web>();
    board_ref.insert(board_ref.to_index(12, 4), saurion_web_id);
    players_manager_ref.add_entity_for_player(enemy_id, saurion_web_id);

    auto make_web_poison_connection = [native_id]() {
        return make_every_two_turns_from_next_callback_holder(std::numeric_limits<std::int32_t>::max(),
                                                              [native_id]() {
                                                                  std::cout << "receive damage\n";
                                                                  damage_dealers::standard_damage_dealer(
                                                                          special_damage(4, native_id));
                                                              });
    };

    auto web_poison_connection = make_every_two_turns_from_next_callback_holder(
            std::numeric_limits<std::int32_t>::max(),
            [native_id]() {
                std::cout << "receive damage\n";
                damage_dealers::standard_damage_dealer(
                        special_damage(4, native_id));
            });
    std::shared_ptr<turn_scoped_connection> connection =
            std::make_shared<turn_scoped_connection>(std::move(web_poison_connection));


    entity_manager_ref.on_destroy(saurion_web_id,
                                  [&players_manager_ref, tester_id, native_id, connection]() mutable {
                                      connection = nullptr;
                                      players_manager_ref.add_entity_for_player(tester_id, native_id);
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