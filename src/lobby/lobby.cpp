#include <mutex>
#include <unordered_map>

#include <boost/program_options.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <tbb/concurrent_hash_map.h>

#include <json.hpp>

#include <networking/server.h>
#include <logging/logger.h>
#include <lobby/game_handler.h>
#include <lobby/game_request_supervisor.h>
#include <lobby/player_handler.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
  init_logging();

  namespace po = boost::program_options;
  po::options_description desc("Lobby options");
  desc.add_options()
      ("help", "Shows help message")
      ("port,p", po::value<std::int32_t>()->default_value(60000), "Sets port on which the lobby server is running")
      ("game_exec,g", po::value<std::string>()->required(), "Path to the game executable");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  }

  auto port = vm.at("port").as<std::int32_t>();
  auto game_exec = vm.at("game_exec").as<std::string>();

  networking::server<networking::web_socket_connection> server(port);

  using game_handlers_map = tbb::concurrent_hash_map<std::string, std::shared_ptr<game_handler>>;
  using game_handler_accessor = game_handlers_map::accessor;
  game_handlers_map game_handlers;

  using player_handlers_map = tbb::concurrent_hash_map<std::uint32_t, std::shared_ptr<player_handler>>;
  using player_handler_accessor = player_handlers_map::accessor;
  player_handlers_map player_handlers;

  game_request_supervisor game_request_supervisor(game_handler_factory(game_exec, port + 1),
                                                  game_handlers,
                                                  player_handlers);

  // TODO: how to clear the games that are not active any more???!!!
  // TODO: we need to close both - web socket connection and also the game <-> handler connection!

  server.on_client_accepted([&](std::shared_ptr<networking::web_socket_connection> client) mutable {
    const auto client_id = client->get_id();
    LOG(debug) << "new player with id: " << client_id << " connected";
    auto handler = std::make_shared<player_handler>(server, client_id);
    player_handlers.emplace(std::piecewise_construct, std::make_tuple(client_id), std::make_tuple(handler));
  });

  server.on_client_disconnect([&](std::shared_ptr<networking::web_socket_connection> client) {
    const auto client_id = client->get_id();
    LOG(debug) << "player with id: " << client_id << " disconnected";
    player_handler_accessor accessor;
    if (player_handlers.find(accessor, client_id)) {
      accessor->second->set_disconnected();
    } else {
      LOG(error) << "player with id: " << client_id << " disconnected, but there is no handler for it!";
    }
  });

  // TODO: split scenario loading from normal message forwarding
  server.on_message([&](std::uint32_t client_id, const std::string& message) {
    using json_data_type = nlohmann::json;

    json_data_type data;
    try {
      data = json_data_type::parse(message);
    } catch (std::exception& e) {
      LOG(error) << "Message parsing error in: " << message << ", what: " << e.what();
    }

    if (data.count("game_request")) {
      std::string game_hash = data["game_request"]["game_hash"];
      std::int32_t number_of_players = data["game_request"]["number_of_players"];

      LOG(debug) << "Got game_request message: game_hash: " << game_hash;

      if (game_hash.empty() && number_of_players != 1) {
        game_request_supervisor.find_opponent_and_create_game(client_id);

      } else if (game_handlers.count(game_hash) > 0) {
        game_request_supervisor.join_game(client_id, game_hash);

      } else {
        std::string scenario = data["game_request"]["scenario"];
        std::string map = data["game_request"]["map"];
        game_request_supervisor.create_game(client_id, game_hash, scenario, map, number_of_players);
      }

    } else {
      LOG(debug) << "got message from client of id: " << client_id << ", which is: " << message;
      player_handler_accessor accessor;
      if (player_handlers.find(accessor, client_id)) {
        accessor->second->send(message);
      } else {
        LOG(error) << "there is no player with id: " << client_id << " while sending the message to it!";
      }
    }
  });

  server.start();

  LOG(info) << "Lobby is ready, waiting for players...";

  while (!processing_interrupted) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    // collect players that are disconnected above disconnection time threshold
    // for all disconnected players we need to remove its clients

    std::vector<std::uint32_t> outdated_disconnections;
    for (const auto& player_handler : player_handlers) {
      if (player_handler.second->disconnected_timeouted()) {
        outdated_disconnections.push_back(player_handler.first);
      }
    }

    // warning: removal from player_handlers can race with on_client_accepted
    for (auto player_id : outdated_disconnections) {
      LOG(debug) << "removing player with id: " << player_id;

      // This is also updating the game_handler by removing its player
      player_handlers.erase(player_id);
    }

    // collect game handlers that do not have any players
    std::vector<std::string> invalid_games;
    for (const auto& game_handler : game_handlers) {
      if (game_handler.second->is_invalid()) {
        invalid_games.push_back(game_handler.first);
      }
    }

    for (auto game_hash : invalid_games) {
      LOG(debug) << "removing game with hash: " << game_hash;
      game_handlers.erase(game_hash);
    }

    LOG(debug) << "number of games: " << game_handlers.size();
    LOG(debug) << "number of players: " << player_handlers.size();
  }
  server.stop();

  LOG(info) << "Lobby finishing.";

  return 0;
}
