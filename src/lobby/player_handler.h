#pragma once

#include <atomic>
#include <chrono>

#include <networking/client.h>
#include <networking/server.h>
#include <lobby/game_handler.h>

class player_handler {
 public:
  using server_type = networking::server<networking::web_socket_connection>;
  static constexpr auto localhost = "127.0.0.1";

  player_handler(server_type& server, std::uint32_t player_id);

  ~player_handler();

  void add_to_game(game_handler& game_handler);

  void send(std::string message);

  [[nodiscard]] bool is_valid() const;

  void set_disconnected();

  [[nodiscard]] bool disconnected_timeouted() const;

 private:
  void remove_from_game();

  std::chrono::steady_clock::duration disconnection_timeout_{std::chrono::minutes(1)};

  server_type& server_;
  std::uint32_t player_id_;
  game_handler* game_handler_{nullptr};
  bool disconnected_{false};
  std::chrono::steady_clock::time_point disconnection_time_;

  networking::client client_;
  std::atomic_bool is_working_{false};
  std::thread worker_;
};
