#include <chrono>
#include <thread>

#include <json.hpp>

#include <logging/logger.h>

#include <turn_based/game_controller.h>
#include <get_button_description.h>
#include <get_effect_description.h>
#include <get_entity_description.h>
#include <get_game_state.h>

#include <get_entities.h>
#include <networking/server.h>
#include <networking/socket_connection.h>
#include <turn_based/board.h>
#include <turn_based/event_center.h>
#include <turn_based/managers/players_manager.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/scenario_factory.h>
#include <turn_based/sender.h>

#include <message_processor.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
  std::signal(SIGINT, &interrupt_processing);

  init_logging();

  // TODO: nice parsing parameters from argv
  std::int32_t port = 60001;
//  std::string scenario = "saurian_web";
  std::string scenario = "skirmish";
  std::string map;
  std::int32_t number_of_players = 1;
  std::pair<std::uint32_t, std::uint32_t> map_size{15, 10};

  if (argc > 1) {
    port = std::atoi(argv[1]);
  }
  if (argc >= 3) {
    scenario = std::string(argv[2]);
  }
  if (argc == 4) {
    map = std::string(argv[3]);
  }
  if (argc == 5) {
    number_of_players = std::atoi(argv[4]);
  }

  game::get<scenario_factory>().create(scenario);

  networking::server<networking::socket_connection> server(port);
  LOG(debug) << "Loading game server on port: " << port;

  sender::set_sender([&server](std::string message) {
    server.send_message_to_all(message);
  });

  std::int32_t connected_players = 0;
  LOG(debug) << "number_of_players: " << number_of_players << ", while connected_players: " << connected_players;

  // TODO: do we want to use client_id or connection ptr??
  server.on_client_accepted([&](std::shared_ptr<networking::socket_connection> client) {
    const auto client_id = client->get_id();
    LOG(debug) << "new client accepted with id: " << client_id;
    LOG(debug) << "Sending initial messages to client";

    server.send_message(client->get_id(), make_map_size_message(map_size));
    server.send_message(client->get_id(), make_client_id_message(client->get_id()));
    server.send_message(client->get_id(), make_map_name_message(scenario));
    server.send_message(client->get_id(), make_entities_pack_message(get_entities()));
    game::get<event_center>().emit(events::CLIENT_ACCEPTED);

    ++connected_players;
    if (connected_players == number_of_players) {
      server.send_message_to_all(make_game_ready_message());
    }

    LOG(debug) << "Sending initial messages to client ready";
  });

  using json_data_type = nlohmann::json;

  message_processor message_processor;

  server.on_message([&](std::uint32_t client_id, const std::string& message) {
    LOG(debug) << "got new message: " << message << ", from client: " << client_id;
    message_processor.execute(message);
  });

  message_processor.bind("on_board", [&](json_data_type& data) {
    LOG(debug) << "on board";

    std::int32_t client_id = data["client_id"];
    std::uint32_t x = data["col"];
    std::uint32_t y = data["row"];

    bool single_client = server.number_of_clients() == 1;

    LOG(debug) << "is single client: " << single_client;
    LOG(debug) << "client_id: " << client_id;
    LOG(debug) << "get_active_player_id: " << game::get<players_manager>().get_active_player_id();

    if (client_id == game::get<players_manager>().get_active_player_id().cast() || single_client) {
      LOG(debug) << "executing on board and sending local and global state";
      game_control().on_board(x, y);
      server.send_message_to_all(make_local_game_state_message(get_local_game_state()));
      server.send_message_to_all(make_global_game_state_message(get_global_game_state()));
    }
  });

  message_processor.bind("on_button", [&](json_data_type& data) {
    LOG(debug) << "on button";

    std::int32_t client_id = data["client_id"];
    std::uint32_t button = data["button"];

    const bool single_client = server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id().cast() || single_client) {
      LOG(debug) << "client_id: " << client_id << " single_client:" << single_client;
      game_control().on_button(button);

      if (button == 5) {
        auto active_player = game::get<players_manager>().get_active_player_id();
        server.send_message_to_all(make_end_turn_message(active_player));
      }

      server.send_message_to_all(make_local_game_state_message(get_local_game_state()));
      server.send_message_to_all(make_global_game_state_message(get_global_game_state()));
    }
  });

  message_processor.bind("get_entity_description", [&](json_data_type& data) {
    // TODO: uint32 or int32??
    std::uint32_t client_id = data["client_id"];

    std::string description;

    const bool single_client = server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id().cast() || single_client) {
      description = get_entity_description(game_control().selected_index);
      server.send_message(client_id, make_entity_description_message(description));
    }
  });

  message_processor.bind("get_button_description", [&](json_data_type& data) {
    // TODO: uint32 or int32??
    std::uint32_t client_id = data["client_id"];
    std::uint32_t button = data["button"];

    std::string description;

    const bool single_client = server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id().cast() || single_client) {

      description = get_button_description(game_control().selected_index, button);
      server.send_message(client_id, make_description_message(description));
    }
  });

  message_processor.bind("get_effect_description", [&](json_data_type& data) {
    std::int32_t client_id = data["client_id"];
    std::string effect = data["effect"];

    std::string description;

    const bool single_client = server.number_of_clients() == 1;

    if (client_id == game::get<players_manager>().get_active_player_id().cast() || single_client) {
      description = get_effect_description(effect);
      server.send_message(client_id, make_effect_description_message(description));
    }
  });

  server.start();
  while (!processing_interrupted) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  server.stop();

  LOG(debug) << "server finishing.";

  return 0;
}
