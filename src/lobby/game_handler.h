#pragma once

#include <memory>
#include <mutex>
#include <unordered_set>

#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <tbb/concurrent_unordered_set.h>

#include <lobby/executable.h>
#include <logging/logger.h>

// How we can split this:
// - executable: RAII wrapper over executable with its arguments
// - players_set: manages adding and removing players, provides observers to check if all players are added
// - port_provider: manages set of available ports
// - game_handler: combines: executable and players_set
// - game_handler_factory: creates a game_handler with provided arguments

class players_set {
 public:
  explicit players_set(std::uint32_t number_of_players);
  bool add_player(std::uint32_t player_id);
  void remove_player(std::uint32_t player_id);
  bool all_players_added() const;
  bool anyone_added() const;
  std::size_t number_of_added_players() const;
  bool has_all_players() const;
  bool all_removed() const;

 private:
  mutable std::mutex mtx_;
  std::uint32_t number_of_players_{0};
  bool anyone_added_{false};
  std::unordered_set<std::uint32_t> players_;
};


// TODO: what is a game_handler:
// - so it launches the provided executable as a separate process with provided arguments
// - it keeps the port on which the game is running
// - it keeps the players collection that are in the game (just a set) and allows to add and remove them
// - destroying this will also terminate the executable
// So generally, this is a RAII wrapper over executable with some parameters about the game, like players

struct game_arguments {
  std::string game_path;
  std::int32_t port{0};
  std::string scenario;
  std::string map;
  std::uint32_t number_of_players{0};
};

class game_handler : public players_set {
 public:
  explicit game_handler(const game_arguments& arguments);

  [[nodiscard]] std::int32_t get_port() const {
    return port_;
  }

 private:
  executable_ptr executable_;
  std::int32_t port_;
};

using port_t = std::int32_t;
using scoped_port_t = std::shared_ptr<port_t>;

// This class maintains a list of available ports
class port_provider {
 public:
  // TODO: maybe we can make port be RAII??
  // it can be shared_ptr with special deleter :thinking

  explicit port_provider(std::int32_t initial_port) : port_generator_(initial_port), max_port_(initial_port + 1000) {}

  std::int32_t get_port() {
    auto port = get_next_available_port();
    used_ports_.insert(port);
    return port;
  }

  void free_port(std::int32_t port) {
    available_ports_.insert(port);
    used_ports_.erase(port);
  }

 private:
  std::int32_t get_next_available_port() {
    if (!available_ports_.empty()) {
      const auto it = available_ports_.cbegin();
      const auto port = *it;
      available_ports_.erase(it);
      return port;
    }
    if (port_generator_ <= max_port_) {
      return port_generator_++;
    }
    throw std::runtime_error("port_handler: reached limit for ports!");
  }

  void generate_available_ports(std::int32_t max_ports) {
    for (std::int32_t port = 0; port < max_ports; ++port) {
      available_ports_.insert(port);
    }
  }

  std::int32_t port_generator_{0};
  std::int32_t max_port_;
  std::unordered_set<std::int32_t> available_ports_;
  std::unordered_set<std::int32_t> used_ports_;
};

// TODO: come up with well designed modularity that will be testable without full game
// So: this class is a game handler factory:
// - it takes some executable path
// - it manages available ports through port_provider class
// - it allows to create a game handlers with provided: executable path, available port,
// scenario, map and number of players: basically, all executable arguments.
class game_handler_factory {
 public:
  using path = boost::filesystem::path;

  game_handler_factory(
      path game_executable_path, std::int32_t initial_port)
      : game_executable_path_(std::move(game_executable_path)), port_provider_(initial_port) {
  }

  std::shared_ptr<game_handler> make_game_handler(
      const std::string& scenario, const std::string& map, std::uint32_t number_of_players) {
    game_arguments arguments;
    arguments.game_path = game_executable_path_.string();
    arguments.port = port_provider_.get_port();
    arguments.scenario = scenario;
    arguments.map = map;
    arguments.number_of_players = number_of_players;
    return std::make_shared<game_handler>(arguments);
  }

 private:
  boost::filesystem::path game_executable_path_;
  port_provider port_provider_;
};
