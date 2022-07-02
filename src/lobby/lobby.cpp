#include <unordered_map>

#include <boost/program_options.hpp>

#include <external/json.hpp>

#include <networking/server.h>
#include <turn_based/logger.h>
#include <lobby/game_handler.h>
#include <lobby/player_handler.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
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

  game_handler_factory game_handler_factory(game_exec, port + 1);

  std::vector<game_handler> game_handlers;
  std::unordered_map<std::uint32_t, std::shared_ptr<player_handler>> player_handlers;

  server.on_client_accepted([&](std::shared_ptr<networking::web_socket_connection> client) mutable {
    const auto client_id = client->get_id();
    LOG(debug) << "new player connected with id: " << client_id;

    //game_handlers.emplace_back(game_handler_factory.make_game_handler());

    // Sleep to initialize the game
    //std::this_thread::sleep_for(std::chrono::seconds(1)); // maybe here is too much

    // create player handler
    auto handler = std::make_shared<player_handler>(server, client_id);
    //handler->add_to_game(game_handlers.back());
    player_handlers.emplace(std::piecewise_construct, std::make_tuple(client_id), std::make_tuple(handler));

    LOG(debug) << "Game created for client";
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

    if (data.count("configure")) {
      std::string scenario = data["configure"]["scenario"];
      std::string map = data["configure"]["map"];
      LOG(debug) << "Got configuration message: scenario: " << scenario << ", map: " << map;

      game_handlers.emplace_back(game_handler_factory.make_game_handler(scenario, map));
      std::this_thread::sleep_for(std::chrono::seconds(1)); // maybe here is too much
      player_handlers.at(client_id)->add_to_game(game_handlers.back());

      return;
    }

    LOG(debug) << "got message from client of id: " << client_id << ", which is: " << message;
    player_handlers.at(client_id)->send(message);
  });

  server.start();

  LOG(info) << "Lobby is ready, waiting for players...";

  while (!processing_interrupted) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
  }
  server.stop();

  LOG(info) << "Lobby finishing.";

  return 0;
}
