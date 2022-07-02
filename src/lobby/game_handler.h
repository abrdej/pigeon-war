#pragma once

#include <boost/process.hpp>
#include <boost/filesystem.hpp>

class game_handler {
 public:
  game_handler(const boost::filesystem::path& game_exec_file, std::int32_t port);

  [[nodiscard]] std::int32_t get_port() const {
    return port_;
  }

 private:
  boost::process::child game_process_;
  std::int32_t port_;
};

class game_handler_factory {
 public:
  game_handler_factory(boost::filesystem::path game_exec_file, std::int32_t first_port)
      : game_exec_file_(std::move(game_exec_file)), first_port_(first_port) {
  }

  game_handler make_game_handler() {
    return {game_exec_file_, first_port_ + game_id_++};
  }

 private:
  boost::filesystem::path game_exec_file_;
  std::int32_t first_port_;
  std::int32_t game_id_{0};
};
