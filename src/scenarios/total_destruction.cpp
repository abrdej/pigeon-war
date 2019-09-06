#include <scenarios/total_destruction.h>

#include <ai/ai_factories.h>
#include <ai/ai_manager.h>
#include <entities/destroyer.h>
#include <entities/golem.h>
#include <entities/shooter.h>
#include <entities/warrior.h>
#include <entities/wolf.h>

void scenarios::create_total_destruction() {
  game_board().set_size(15, 10);

  auto tester_id = game_get<players_manager>().create_human_player("tester");
  auto enemy_id = game_get<players_manager>().create_ai_player("enemy");

  auto destroyer_id = game::get<entity_manager>().create<destroyer>();
  game_board().insert(game_board().to_index(7, 5), destroyer_id);

  game_get<players_manager>().add_entity_for_player(tester_id, destroyer_id);

  std::vector<std::uint32_t> wolves_indexes = {
      game_board().to_index(2, 1),  game_board().to_index(2, 3),  game_board().to_index(2, 5),
      game_board().to_index(2, 7),  game_board().to_index(4, 1),  game_board().to_index(6, 1),
      game_board().to_index(8, 1),  game_board().to_index(10, 1), game_board().to_index(12, 1),
      game_board().to_index(12, 3), game_board().to_index(12, 5), game_board().to_index(12, 7)};

  for (auto&& wolve_index : wolves_indexes) {
    auto wolf_id = game::get<entity_manager>().create<wolf>();
    game_board().insert(wolve_index, wolf_id);
    game_get<players_manager>().add_entity_for_player(enemy_id, wolf_id);
    game_get<ai_manager>().add_ai_for(wolf_id, ai::make_ai<wolf>());
  }

  set_after_n_round_callback(2, [tester_id]() {
    auto shooter_id = game::get<entity_manager>().create<shooter>();
    auto warrior_id = game::get<entity_manager>().create<warrior>();
    auto golem_id = game::get<entity_manager>().create<golem>();

    game_get<players_manager>().add_entity_for_player(tester_id, shooter_id);
    game_get<players_manager>().add_entity_for_player(tester_id, warrior_id);
    game_get<players_manager>().add_entity_for_player(tester_id, golem_id);

    std::vector<std::uint32_t> free_fields;
    board_helper::all_free(free_fields);

    game_board().insert(free_fields[0], shooter_id);
    game_board().insert(free_fields[4], warrior_id);
    game_board().insert(free_fields[8], golem_id);

    sender::send(make_create_entity_message(shooter_id));
    sender::send(make_create_entity_message(warrior_id));
    sender::send(make_create_entity_message(golem_id));
  });
}
