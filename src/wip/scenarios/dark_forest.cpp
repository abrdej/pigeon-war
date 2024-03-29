#include <dark_forest.h>

#include <ai/ai_factories.h>
#include <ai/ai_manager.h>
#include <turn_based/board.h>
#include <wip/entities/pixie.h>
#include <entities/samurai_rat/samurai_rat.h>
#include <wip/entities/spectre.h>
#include <turn_based/creator_helper.h>
#include <turn_based/map_reader.h>
#include <turn_based/scenario_helper.h>

void scenario::create_dark_forest() {
  std::pair<uint32_t, uint32_t> map_size;
  read_map_from_json(maps_directory + "dark_forest.json", map_size);

  auto& players_manager_ref = game_get<players_manager>();

  auto samurai_id = game::get<entity_manager>().create<samurai_rat>();
  auto spectre_id = game::get<entity_manager>().create<spectre>();

  game_board().insert(game_board().to_index(2, 5), samurai_id);
  game_board().insert(game_board().to_index(13, 5), spectre_id);

  auto tester_id = players_manager_ref.create_human_player("tester");
  auto enemy_id = players_manager_ref.create_ai_player("enemy");

  players_manager_ref.add_entity_for_player(tester_id, samurai_id);
  players_manager_ref.add_entity_for_player(enemy_id, spectre_id);

  game::get<ai_manager>().add_ai_for(spectre_id, ai::make_ai<spectre>());

  using creator_helper::pos;
  std::vector<std::pair<std::uint32_t, std::uint32_t>> pixies_positions = {
      pos(2, 0), pos(4, 1), pos(5, 7), pos(7, 2), pos(7, 5)};
  for (auto&& pixie_pos : pixies_positions) {
    auto pixie_id = game::get<entity_manager>().create<pixie>();
    game::get<ai_manager>().add_ai_for(pixie_id, ai::make_ai<pixie>());
    game_board().insert(game_board().to_index(pixie_pos.first, pixie_pos.second), pixie_id);
    players_manager_ref.add_entity_for_player(enemy_id, pixie_id);
  }

  if_any_die({samurai_id}, [&]() {
    LOG(debug) << "defeat";
    game_control().defeat();
  });
  if_any_die({spectre_id}, [&]() {
    LOG(debug) << "victory";
    game_control().victory(tester_id);
  });
}
