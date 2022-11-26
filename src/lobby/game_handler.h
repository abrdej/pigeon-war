#pragma once

#include <mutex>
#include <unordered_set>

#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <tbb/concurrent_unordered_set.h>

class game_handler {
 public:
  game_handler(const boost::filesystem::path& game_exec_file, std::int32_t port,
               const std::string& scenario, const std::string& map, std::uint32_t number_of_players);

  ~game_handler();

  [[nodiscard]] std::int32_t get_port() const {
    return port_;
  }

  void add_player(std::uint32_t player_id);
  void remove_player(std::uint32_t player_id);

  void start_if_full();

  [[nodiscard]] bool is_invalid() const;

  [[nodiscard]] bool is_full() const;

 private:
  boost::process::child game_process_;
  std::int32_t port_;
  std::uint32_t number_of_players_{0};
  bool anyone_added_{false};
  mutable std::mutex players_mtx_;
  std::unordered_set<std::uint32_t> players_;
  bool started_{false};
};

class game_handler_factory {
 public:
  game_handler_factory(
      boost::filesystem::path game_exec_file, std::int32_t first_port)
      : game_exec_file_(std::move(game_exec_file)), first_port_(first_port) {
  }

  std::shared_ptr<game_handler> make_game_handler(
      const std::string& scenario, const std::string& map, std::uint32_t number_of_players) {
    return std::make_shared<game_handler>(game_exec_file_, first_port_ + game_id_++, scenario, map, number_of_players);
  }

 private:
  boost::filesystem::path game_exec_file_;
  std::int32_t first_port_;
  std::int32_t game_id_{0};
};
