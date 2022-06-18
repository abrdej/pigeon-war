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

struct saurian_web_scenario_factory : public scenario_factory_interface {
  void create() override;
};

void saurian_web_scenario_factory::create() {
  LOG(debug) << "creating saurian web scenario";

  std::pair<uint32_t, uint32_t> map_size;
  read_map_from_json(maps_directory + "saurian_web.json", map_size);
  game_board().set_size(map_size.first, map_size.second);

  auto &entity_manager_ref = game::get<entity_manager>();
  auto &players_manager_ref = game::get<players_manager>();

  auto shooter_id = game::get<entities_factory>().create("shooter");
  auto saberhand_id = game::get<entities_factory>().create("saberhand");
  auto saurian1_id = game::get<entities_factory>().create("saurian");
  auto saurian2_id = game::get<entities_factory>().create("saurian");
  auto saurian3_id = game::get<entities_factory>().create("saurian");
  auto saurian4_id = game::get<entities_factory>().create("saurian");
  auto saurian5_id = game::get<entities_factory>().create("saurian");

  game::get<ai_manager>().add_ai_for(saurian1_id, game::get<ai_factory>().create("saurian_ai"));
  game::get<ai_manager>().add_ai_for(saurian2_id, game::get<ai_factory>().create("saurian_ai"));
  game::get<ai_manager>().add_ai_for(saurian3_id, game::get<ai_factory>().create("saurian_ai"));
  game::get<ai_manager>().add_ai_for(saurian4_id, game::get<ai_factory>().create("saurian_ai"));
  game::get<ai_manager>().add_ai_for(saurian5_id, game::get<ai_factory>().create("saurian_ai"));

  game_board().insert(game_board().to_index(2, 3), shooter_id);
  game_board().insert(game_board().to_index(2, 5), saberhand_id);

  game_board().insert(game_board().to_index(13, 4), saurian1_id);
  game_board().insert(game_board().to_index(12, 2), saurian2_id);
  game_board().insert(game_board().to_index(12, 6), saurian3_id);
  game_board().insert(game_board().to_index(4, 1), saurian4_id);
  game_board().insert(game_board().to_index(7, 9), saurian5_id);

  auto tester_id = players_manager_ref.create_human_player("tester");
  auto enemy_id = players_manager_ref.create_ai_player("enemy");
  players_manager_ref.add_entity_for_player(tester_id, shooter_id);
  players_manager_ref.add_entity_for_player(tester_id, saberhand_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian1_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian2_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian3_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian4_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian5_id);

  auto native_id = game::get<entities_factory>().create("native");
  game_board().insert(game_board().to_index(12, 4), native_id);
  players_manager_ref.add_neutral_entity(native_id);

  auto saurian_web_id = game::get<entities_factory>().create("saurian_web");
  game_board().insert(game_board().to_index(12, 4), saurian_web_id);
  players_manager_ref.add_entity_for_player(enemy_id, saurian_web_id);

  auto web_poison_connection = make_every_two_turns_from_next_callback_holder(
      std::numeric_limits<std::int32_t>::max(), [native_id]() {
        LOG(debug) << "dealing damage to native";
        damage_dealers::standard_damage_dealer(special_damage(4, native_id));
      });
  std::shared_ptr<turn_scoped_connection> connection =
      std::make_shared<turn_scoped_connection>(std::move(web_poison_connection));

  entity_manager_ref.on_destroy(saurian_web_id,
                                [&players_manager_ref, tester_id, native_id, connection]() mutable {
                                  connection = nullptr;
                                  players_manager_ref.add_entity_for_player(tester_id, native_id);

                                  sender::send(make_entity_talk_message(
                                      game_board().index_for(native_id),
                                      "Nie trzeba było chłopaki, już miałem się z nimi rozprawić..."));
                                });

  on_intro([shooter_id, saberhand_id]() {
    sender::send(make_entity_talk_message(game_board().index_for(shooter_id),
                                          "Te jaszczury uwięziły tubylca. "
                                          "Jeśli go uwolnimy powinien do nas dołączyć!"));
    sender::send(make_entity_talk_message(game_board().index_for(saberhand_id),
                                          "Trzeba się tam szybko przedostać"));
    sender::send(make_entity_talk_message(game_board().index_for(shooter_id),
                                          "Niech zakosztują moich kul!"));
  });

  if_any_die({shooter_id, saberhand_id, native_id}, [&]() {
    LOG(debug) << "defeat";
    game_control().defeat();
  });
  if_all_die({saurian1_id, saurian2_id, saurian3_id, saurian4_id},
             [&]() {
               make_entity_talk_message(game_board().index_for(native_id),
                                        "Jaszczury pogrzebane!");
               game_control().victory(tester_id);
             });
}

scenario_factory_interface_ptr create_saurian_web_scenario_factory() {
  return std::make_shared<saurian_web_scenario_factory>();
}

BOOST_DLL_ALIAS(create_saurian_web_scenario_factory, saurian_web)
