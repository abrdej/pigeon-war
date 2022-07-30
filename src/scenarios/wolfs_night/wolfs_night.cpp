#include <boost/dll/alias.hpp>

#include <config.h>
#include <turn_based/map_reader.h>
#include <turn_based/scenario_helper.h>
#include <turn_based/ai/ai_manager.h>
#include <turn_based/ai_factory.h>
#include <turn_based/board.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/entities_factory.h>
#include <turn_based/game.h>
#include <turn_based/game_controller.h>
#include <turn_based/scenario_factory_interface.h>
#include <turn_based/turn_system.h>

struct wolfs_night_scenario_factory : public scenario_factory_interface {
  void create() override;
};

void wolfs_night_scenario_factory::create() {
  LOG(debug) << "creating saurian web scenario";

  std::pair<uint32_t, uint32_t> map_size;
  read_map_from_json(maps_directory + "dark_forest.json", map_size);
  game_board().set_size(map_size.first, map_size.second);

  auto &entity_manager_ref = game::get<entity_manager>();
  auto &players_manager_ref = game::get<players_manager>();

  auto shooter_id = game::get<entities_factory>().create("shooter");

  game_board().insert(game_board().to_index(5, 6), shooter_id);

  auto tester_id = players_manager_ref.create_human_player("tester");
  auto enemy_id = players_manager_ref.create_ai_player("enemy");
  players_manager_ref.add_entity_for_player(tester_id, shooter_id);

  std::vector<entity_id_t> enemies_ids;

  auto spawn_wolf = [&players_manager_ref, enemy_id, enemies_ids](index_t index) mutable {
    auto wolf_id = game::get<entities_factory>().create("wolf");
    game::get<ai_manager>().add_ai_for(wolf_id, game::get<ai_factory>().create("wolf_ai"));
    game_board().insert(index, wolf_id);
    players_manager_ref.add_entity_for_player(enemy_id, wolf_id);
    sender::send(make_create_entity_message(wolf_id));
    enemies_ids.push_back(wolf_id);
  };

  auto spawn_samurai_rat = [&players_manager_ref, tester_id]() mutable {
    auto samurai_rat_id = game::get<entities_factory>().create("samurai_rat");
    game_board().insert(10, samurai_rat_id);
    players_manager_ref.add_entity_for_player(tester_id, samurai_rat_id);

    if_any_die({samurai_rat_id}, [&]() {
      LOG(debug) << "defeat";
      game_control().defeat();
    });

    sender::send(make_create_entity_message(samurai_rat_id));
  };

  std::vector<index_t> spawning_indices = {
      4, 28, 136
  };

  auto spawner_holder = make_every_two_turns_from_next_callback_holder(
      std::numeric_limits<std::int32_t>::max(), [i = 0, spawn_wolf, spawning_indices]() mutable {
        LOG(debug) << "Spawning wolf";
        auto spawn_index = i++ % spawning_indices.size();

        LOG(debug) << "Is slot empty: " << game_board().empty(spawn_index);

        if (game::get<board>().empty(spawn_index)) {
          spawn_wolf(spawning_indices[spawn_index]);
        }
      });

  auto spawner_connection = std::make_shared<turn_scoped_connection>(std::move(spawner_holder));

  set_after_n_round_callback(10, [spawner_connection, spawn_samurai_rat]() mutable {
    spawn_samurai_rat();
    spawner_connection = nullptr;
  });

  on_intro([shooter_id]() {
    sender::send(make_entity_talk_message(game_board().index_for(shooter_id),
                                          "I don't like this place..."));
  });

  if_any_die({shooter_id}, [&]() {
    LOG(debug) << "defeat";
    game_control().defeat();
  });

//  if_all_die({saurian1_id, saurian2_id, saurian3_id, saurian4_id},
//             [&]() {
//               make_entity_talk_message(game_board().index_for(native_id),
//                                        "Jaszczury pogrzebane!");
//               game_control().victory(tester_id);
//             });
}

scenario_factory_interface_ptr create_wolfs_night_scenario_factory() {
  return std::make_shared<wolfs_night_scenario_factory>();
}

BOOST_DLL_ALIAS(create_wolfs_night_scenario_factory, wolfs_night)
