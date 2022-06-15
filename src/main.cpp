#include <iostream>
#include <chrono>
#include <thread>

#include <external/json.hpp>

#include <abilities/abilities.h>

#include <components/applied_effects.h>
#include <components/damage_taker.h>

#include <core/game_controller.h>
#include <core/get_button_description.h>
#include <core/get_effect_description.h>
#include <core/get_game_state.h>

#include <managers/get_entities.h>
#include <managers/get_entity_names.h>

#include <scenarios/battle_with_a_golem_scenario.h>
#include <scenarios/dark_forest.h>
#include <scenarios/saurian_web_scenario.h>
#include <scenarios/skirmish.h>
#include <scenarios/total_destruction.h>
#include <scenarios/wolves_dinner.h>

//#include <server/server.h>
#include <server/new_server.h>

int main(int argc, char** argv) {

  // main server will start this.
  // same initialization will be passed by config file
  // maybe in json
  // map name, entities to select, players token, etc.

  // parse some initial arguments
  // create game
  // set up server
  // run server

  std::int32_t port = 60000;
	std::string map_name = "battlefield";
//  std::string map_name = "winter_forest";
//  std::string map_name = "river_land";
  std::string scenario = "skirmish";
//	std::string scenario = "dark_forest";
  std::pair<std::uint32_t, std::uint32_t> map_size{15, 10};

  if (argc > 1) {
    port = std::atoi(argv[1]);
  }
  if (argc == 4) {
    scenario = std::string(argv[2]);
    map_name = std::string(argv[3]);
  }

  static std::unordered_map<std::string, std::function<void()>>
      scenario_loader = {
      {"skirmish", [&map_name, &map_size]() {
        map_name = create_skirmish(map_name + ".json", map_size);
      }},
      {"saurian_web", []() {
        create_saurian_web();
      }},
      {"wolves_dinner", []() {
        create_wolves_dinner();
      }},
      {"dark_forest", []() {
        scenario::create_dark_forest();
      }}
  };
  scenario_loader.at(scenario)();

  // create game
//    map_name = create_skirmish(map_name, map_size);
  //create_wolves_dinner();
//	create_saurian_web();
//	scenarios::create_total_destruction();
//    scenarios::create_battle_with_a_golem_scenario();
//	map_name = "Battle with a golem";

//  tcp_server pigeon_war_server(port);

  networking::server pigeon_war_server(port);

  sender::set_sender([&pigeon_war_server](std::string message) {
    std::cout << "Sending the message to all\n";
    pigeon_war_server.send_message_to_all(message);
    std::cout << "Sending the message to all: ready\n";
  });

  // TODO: do we want to use client_id or connection ptr??
  pigeon_war_server.on_client_accepted([&](std::shared_ptr<networking::web_socket_connection> client) {
    pigeon_war_server.send_message(client->get_id(), make_map_size_message(map_size));
    pigeon_war_server.send_message(client->get_id(), make_client_id_message(client->get_id()));
    pigeon_war_server.send_message(client->get_id(), make_map_name_message(map_name));
    pigeon_war_server.send_message(client->get_id(), make_entities_pack_message(get_entities()));
  });

  // TODO: this could be extracted as a message processor
  using json_data_type = nlohmann::json;
  using callback_type = std::function<void(json_data_type&)>;
  std::unordered_map<std::string, callback_type> callbacks;

  auto bind = [&](const std::string& message_type, callback_type callback) {
    callbacks.insert(std::make_pair(message_type, callback));
  };

  pigeon_war_server.on_message([&](std::uint32_t client_id, const std::string& message) {
    json_data_type data;

    std::cout << "Got new message: " << message << "\n";

    try {
      data = json_data_type::parse(message);

      std::cout << "data: \n" << data.dump() << "\n";

      for (auto&& callback_pack : callbacks) {
        if (data.count(callback_pack.first)) {
          std::cout << "call callback for message: " << callback_pack.first << "\n";
          callback_pack.second(data[callback_pack.first]);
        }
      }

    } catch (std::exception& e) {
      std::cout << "json parse error!\n";
      std::cout << "in: " << message << "\n";
      std::cout << "what: " << e.what() << "\n";
    }
  });

  bind("on_board", [&](json_data_type& data) {

    std::cout << "on board\n";

    std::int32_t client_id = data["client_id"];
    std::uint32_t x = data["col"];
    std::uint32_t y = data["row"];

    bool single_client = pigeon_war_server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {
      game_control().on_board(x, y);
      pigeon_war_server.send_message_to_all(make_local_game_state_message(get_local_game_state()));
      pigeon_war_server.send_message_to_all(make_global_game_state_message(get_global_game_state()));
    }
  });

  bind("on_button", [&](json_data_type& data) {

    std::cout << "on button\n";

    std::int32_t client_id = data["client_id"];
    std::uint32_t button = data["button"];

    const bool single_client = pigeon_war_server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

      std::cout << "client_id: " << client_id << " single_client:" << single_client << "\n";

      game_control().on_button(button);

      if (button == 5) {
        auto active_player = game::get<players_manager>().get_active_player_id();
        pigeon_war_server.send_message_to_all(make_end_turn_message(active_player));
      }

      pigeon_war_server.send_message_to_all(make_local_game_state_message(get_local_game_state()));
      pigeon_war_server.send_message_to_all(make_global_game_state_message(get_global_game_state()));
    }
  });

  bind("get_button_description", [&](json_data_type& data) {

    // TODO: uint32 or int32??
    std::uint32_t client_id = data["client_id"];
    std::uint32_t button = data["button"];

    std::string description;

    const bool single_client = pigeon_war_server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {

      description = get_button_description(game_control().selected_index_, button);
      pigeon_war_server.send_message(client_id, make_description_message(description));
    }
  });

  bind("get_effect_description", [&](json_data_type& data) {

    std::int32_t client_id = data["client_id"];
    std::string effect = data["effect"];

    std::string description;

    const bool single_client = pigeon_war_server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id() || single_client) {
      description = get_effect_description(effect);
      pigeon_war_server.send_message(client_id, make_effect_description_message(description));
    }
  });

//  pigeon_war_server.run();
//  pigeon_war_server.wait();

  pigeon_war_server.start();
  // TODO: replace this with run: pigeon_war_server.update()

  while (true) {
    pigeon_war_server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  return 0;
}
