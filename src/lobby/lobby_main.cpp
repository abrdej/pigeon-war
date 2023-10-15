#include <mutex>
#include <unordered_map>

#include <boost/program_options.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <tbb/concurrent_hash_map.h>

#include <json.hpp>

#include <networking/server.h>
#include <logging/logger.h>
#include <lobby/connection_type.h>
#include <lobby/game_handler.h>
#include <lobby/game_request_supervisor.h>
#include <lobby/player_handler.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

class game_request_handler {
 public:
  using game_handlers_map = tbb::concurrent_hash_map<std::string, std::shared_ptr<game_handler>>;

  explicit game_request_handler(game_request_supervisor& game_request_supervisor,
                                game_handlers_map& game_handlers)
      : game_request_supervisor_(game_request_supervisor),
        game_handlers_(game_handlers) {}

  bool handle_game_request(std::uint32_t client_id, const std::string& message) {
    using json_data_type = nlohmann::json;

    json_data_type data;
    try {
      data = json_data_type::parse(message);
    } catch (nlohmann::json::parse_error& e) {
      LOG(error) << "Was not able to parse message: " << message << ", issue: " << e.what();
      return false;
    }

    try {
      if (data.count("game_request")) {
        std::string game_hash = data["game_request"]["game_hash"];
        std::int32_t number_of_players = data["game_request"]["number_of_players"];

        LOG(debug) << "Got game_request message: game_hash: " << game_hash;

        if (game_hash.empty() && number_of_players != 1) {
          game_request_supervisor_.find_opponent_and_create_game(client_id);

        } else if (game_handlers_.count(game_hash) > 0) {
          game_request_supervisor_.join_game(client_id, game_hash);

        } else {
          std::string scenario = data["game_request"]["scenario"];
          std::string map = data["game_request"]["map"];
          game_request_supervisor_.create_game(client_id, game_hash, scenario, map, number_of_players);
        }
        return true;
      }
    } catch (nlohmann::json::type_error& e) {
      LOG(error) << "Incorrect game_request definition: " << message << ", issue: " << e.what();
      // TODO: consider to return that request was declined
      return false;
    }
    return false;
  }

 private:
  game_request_supervisor& game_request_supervisor_;
  game_handlers_map& game_handlers_;
};

class lobby {
  using game_handlers_map = tbb::concurrent_hash_map<std::string, std::shared_ptr<game_handler>>;
  using game_handler_accessor = game_handlers_map::accessor;

  using player_handlers_map = tbb::concurrent_hash_map<std::uint32_t, std::shared_ptr<player_handler>>;
  using player_handler_accessor = player_handlers_map::accessor;

 public:
  explicit lobby(const std::string& game_exec, std::int32_t port)
      : server_(port),
        game_request_supervisor_(game_handler_factory(game_exec, port + 1),
                                 game_handlers_,
                                 player_handlers_),
        game_request_handler_(game_request_supervisor_, game_handlers_) {
    server_.on_client_accepted([this](auto client) {
      on_client_accepted(client);
    });
    server_.on_client_disconnect([this](auto client) {
      on_client_disconnect(client);
    });
    server_.on_message([this](std::uint32_t client_id, const std::string& message) {
      on_message(client_id, message);
    });
  }

  void run() {
    run_impl();
  }

 private:
  void on_client_accepted(std::shared_ptr<connection_type> client) {
    const auto client_id = client->get_id();
    LOG(debug) << "new player with id: " << client_id << " connected";
    auto handler = std::make_shared<player_handler>(server_, client_id);
    player_handlers_.emplace(std::piecewise_construct, std::make_tuple(client_id), std::make_tuple(handler));
  }

  void on_client_disconnect(std::shared_ptr<connection_type> client) {
    const auto client_id = client->get_id();
    player_handler_accessor accessor;
    if (player_handlers_.find(accessor, client_id)) {
      accessor->second->set_disconnected();
      LOG(debug) << "player with id: " << client_id << " disconnected";
    } else {
      LOG(error) << "player with id: " << client_id << " disconnected, but there is no handler for it!";
    }
  }

  void on_message(std::uint32_t client_id, const std::string& message) {
    if (game_request_handler_.handle_game_request(client_id, message)) {
      return;
    }
    // This case just forwards a message to a client
    LOG(debug) << "got message from client of id: " << client_id << ", which is: " << message;
    player_handler_accessor accessor;
    if (player_handlers_.find(accessor, client_id)) {
      accessor->second->send(message);
    } else {
      LOG(error) << "there is no player with id: " << client_id << " while sending the message to it!";
    }
  }

  void run_impl() {
    server_.start();

    LOG(info) << "Lobby is ready, waiting for players...";

    while (!processing_interrupted) {
      server_.update();
      std::this_thread::sleep_for(std::chrono::milliseconds(25));

      // collect players that are disconnected above disconnection time threshold
      // for all disconnected players we need to remove its clients

      std::vector<std::uint32_t> outdated_disconnections;
      for (const auto& player_handler : player_handlers_) {
        if (player_handler.second->disconnected_timeouted()) {
          outdated_disconnections.push_back(player_handler.first);
        }
      }

      // warning: removal from player_handlers can race with on_client_accepted
      for (auto player_id : outdated_disconnections) {
        LOG(debug) << "removing player with id: " << player_id;

        // This is also updating the game_handler by removing its player
        player_handlers_.erase(player_id);
      }

      // collect game handlers that do not have any players
      std::vector<std::string> invalid_games;
      for (const auto& game_handler : game_handlers_) {
        if (game_handler.second->all_removed()) {
          invalid_games.push_back(game_handler.first);
        }
      }

      for (auto game_hash : invalid_games) {
        LOG(debug) << "removing game with hash: " << game_hash;
        game_handlers_.erase(game_hash);
      }
    }
    server_.stop();
  }

  networking::server<connection_type> server_;
  game_handlers_map game_handlers_;
  player_handlers_map player_handlers_;
  game_request_supervisor game_request_supervisor_;
  game_request_handler game_request_handler_;
};

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

  lobby lobby(game_exec, port);
  lobby.run();

  LOG(info) << "Lobby finishing.";

  return 0;
}
