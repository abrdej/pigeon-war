#include <boost/dll/alias.hpp>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/creator_helper.h>
#include <turn_based/entities_factory.h>
#include <turn_based/entities_reader.h>
#include <turn_based/game.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>
#include <turn_based/map_reader.h>
#include <turn_based/scenario_factory_interface.h>
#include <turn_based/scenario_helper.h>
#include <turn_based/turn_system.h>

//auto get_entities_selecting_positions() {
//  return std::vector<creator_helper::pos_type>{
//      {5u, 2u}, {6, 2}, {7, 2}, {8, 2}, {9, 2},
//      {5, 3}, {9, 3},
//      {5, 4}, {9, 4},
//      {5, 5}, {9, 5},
//      {5, 6}, {6, 6}, {7, 6}, {8, 6}, {9, 6}};
//}

auto get_entities_selecting_positions() {
  return std::vector<creator_helper::pos_type>{
      {5, 2}, {7, 2}, {9, 2},
      {5, 4},         {9, 4},
      {5, 6}, {7, 6}, {9, 6}};
}

auto get_entities_starting_positions() {
  return std::vector<creator_helper::pos_type>{
      {2, 2}, {12, 2}, {2, 4}, {12, 4}, {2, 6}, {12, 6}, {2, 8}, {12, 8}};
}

struct skirmish_scenario_factory : public scenario_factory_interface {
  void create() override;
};

void skirmish_scenario_factory::create() {
  // TODO: how to choose map
  // TODO: how to set player nicks

  std::pair<uint32_t, uint32_t> map_size;
  auto name = read_map_from_json(maps_directory + "battlefield.json", map_size);

  const int number_of_players = 2;
  std::array<std::uint32_t, number_of_players> players = {};
  for (auto& player : players) {
    player = game::get<players_manager>().create_human_player("");
  }

  const auto selecting_positions = get_entities_selecting_positions();
  std::unordered_set<entity_id_t> entities_to_choose;

  const auto entities = read_entities_from_json(config_directory + "entities.json");
  for (std::size_t i = 0; i < std::min(selecting_positions.size(), entities.size()); ++i) {
    auto entity_id = game::get<entities_factory>().create(entities[i]);
    auto entity_position = selecting_positions[i];
    game_board().insert(game_board().to_index(entity_position.first, entity_position.second), entity_id);
    game::get<players_manager>().add_neutral_entity(entity_id);
    entities_to_choose.insert(entity_id);
  }

  auto create_entities_container = []() {
    return std::unordered_map<std::uint32_t, std::vector<entity_id_t>>();
  };
  const std::int32_t entities_for_player = 4;

  set_every_turn_callback(
      entities_for_player * number_of_players,
      [starting_positions = get_entities_starting_positions(),
          entities_to_choose,
          players,
          selections = 0, entities = create_entities_container()](const turn_callback_info& info) mutable {
        auto starting_position = starting_positions[selections];
        auto starting_index = game_board().to_index(starting_position.first, starting_position.second);

        auto entity_id = game_board().move(game_control().selected_index_, starting_index);
        sender::send(make_move_entity_message(entity_id, game_control().selected_index_, starting_index));

        entities[players[selections % number_of_players]].push_back(entity_id);

        game_control().selected_index_ = starting_index;

        entities_to_choose.erase(entity_id);

        ++selections;

        if (info.is_ending) {
          LOG(debug) << "Need to destroy the following entities: " << entities_to_choose.size();

          for (auto entity_to_remove : entities_to_choose) {
            game::get<entity_manager>().destroy(entity_to_remove);
          }

          for (const auto& player_pack : entities) {
            for (auto id : player_pack.second) {
              game::get<players_manager>().add_entity_for_player(player_pack.first, id);
            }
          }

          for (const auto& player_pack : entities) {
            if_all_die(player_pack.second, [&]() {
              LOG(debug) << "Player of id: " << player_pack.first << "win!!!";
              game_control().victory(player_pack.first);
            });
          }

          entities.clear();
        }
      });
}

scenario_factory_interface_ptr create_skirmish_scenario_factory() {
  return std::make_shared<skirmish_scenario_factory>();
}

BOOST_DLL_ALIAS(create_skirmish_scenario_factory, skirmish)
