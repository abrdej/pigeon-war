#include <boost/dll/alias.hpp>

#include <config.h>
#include <impl/scenarios/creator_helper.h>
#include <impl/scenarios/map_reader.h>
#include <impl/scenarios/scenario_helper.h>
#include <turn_based/ai/ai_manager.h>
#include <turn_based/ai_factory.h>
#include <turn_based/board.h>
#include <turn_based/entities_factory.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/players_manager.h>
#include <turn_based/scenario_factory_interface.h>

struct wolves_dinner_scenario_factory : public scenario_factory_interface {
  void create() override;
};

void wolves_dinner_scenario_factory::create() {
  LOG(debug) << "creating wolves dinner scenario";

  std::pair<uint32_t, uint32_t> map_size;
  read_map_from_json(maps_directory + "wolves_dinner.json", map_size);
  game_board().set_size(map_size.first, map_size.second);

  auto& players_manager_ref = game_get<players_manager>();

  auto samurai_id = game::get<entities_factory>().create("samurai_rat");

  game_board().insert(game_board().to_index(2, 5), samurai_id);

  auto tester_id = players_manager_ref.create_human_player("tester");
  auto enemy_id = players_manager_ref.create_ai_player("enemy");

  players_manager_ref.add_entity_for_player(tester_id, samurai_id);

  using creator_helper::pos;
  std::vector<std::pair<std::uint32_t, std::uint32_t>> wolves_positions = {
      pos(5, 6), pos(9, 7), pos(12, 2), pos(12, 6), pos(8, 2)};
  std::vector<std::uint32_t> enemies_ids;
  for (auto&& wolf_pos : wolves_positions) {
    auto wolf_id = game::get<entities_factory>().create("wolf");
    game::get<ai_manager>().add_ai_for(wolf_id, game::get<ai_factory>().create("wolf_ai"));
    game_board().insert(game_board().to_index(wolf_pos.first, wolf_pos.second), wolf_id);
    players_manager_ref.add_entity_for_player(enemy_id, wolf_id);
    enemies_ids.push_back(wolf_id);
  }

  if_any_die({samurai_id}, [&]() {
    LOG(debug) << "defeat";
    game_control().defeat();
  });
  if_all_die(enemies_ids, [&]() {
    LOG(debug) << "victory";
    game_control().victory(tester_id);
  });
}

scenario_factory_interface_ptr create_wolves_dinner_scenario_factory() {
  return std::make_shared<wolves_dinner_scenario_factory>();
}

BOOST_DLL_ALIAS(create_wolves_dinner_scenario_factory, wolves_dinner)
