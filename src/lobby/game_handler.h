#pragma once

#include <unordered_set>

#include <boost/process.hpp>
#include <boost/filesystem.hpp>

class game_handler {
 public:
  game_handler(const boost::filesystem::path& game_exec_file,
               std::int32_t port, const std::string& scenario, const std::string& map);

  [[nodiscard]] std::int32_t get_port() const {
    return port_;
  }

  void add_player(std::uint32_t player_id);
  void remove_player(std::uint32_t player_id);

  [[nodiscard]] bool is_valid() const;

 private:
  boost::process::child game_process_;
  std::int32_t port_;
  std::unordered_set<std::uint32_t> players_;
};

class game_handler_factory {
 public:
  game_handler_factory(boost::filesystem::path game_exec_file, std::int32_t first_port)
      : game_exec_file_(std::move(game_exec_file)), first_port_(first_port) {
  }

  game_handler make_game_handler(const std::string& scenario, const std::string& map) {
    return {game_exec_file_, first_port_ + game_id_++, scenario, map};
  }

 private:
  boost::filesystem::path game_exec_file_;
  std::int32_t first_port_;
  std::int32_t game_id_{0};
};
