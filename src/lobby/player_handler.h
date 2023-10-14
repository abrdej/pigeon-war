#pragma once

#include <atomic>
#include <chrono>

#include <networking/client.h>
#include <networking/server.h>
#include <lobby/game_handler.h>

// Here we want to have:
// - server & client: will handle message passing from and to
// - player_handler: manages adding and removing players from players_set
// - combined server & client and player_handler: ??

// TODO: what is a player_handler:
// - it abstract the networking client and connects the client with its server:
//   - forwards messages from client to proper server
//   - forwards messages from server to the client
//
// - It will start a client and call its update
// - It can be added to the game, that will:
//      - connect to the game server (executable)
//      - Add this client to game handler clients collection

//  - It can be also disconnected
//  - Destroying will also remove it from game and close the client connection (so the game executable will lose it)

class network_connection {
 public:
  using server_type = networking::server<networking::web_socket_connection>;
  static constexpr auto localhost = "127.0.0.1";

  explicit network_connection(server_type& server, std::int32_t client_id);

  ~network_connection();

  void connect_to_port(std::int32_t port);

  void send(std::string message);

  [[nodiscard]] bool is_connected() const;

  void set_disconnected();

  [[nodiscard]] bool disconnected_timeouted() const;

 private:
  std::chrono::steady_clock::duration disconnection_timeout_{std::chrono::minutes(1)};

  server_type& server_;
  bool disconnected_{false};
  std::chrono::steady_clock::time_point disconnection_time_;

  networking::client client_;
  std::atomic_bool is_working_{false};
  std::thread worker_;
};

class player_connector {
 public:
  explicit player_connector(std::uint32_t player_id);
  ~player_connector();

  void add_to_game(game_handler& game_handler);
  bool is_valid() const {
    return game_handler_;
  }

 private:
  void remove_from_game();

  std::uint32_t player_id_;
  game_handler* game_handler_{nullptr};
};

class player_handler {
 public:
  using server_type = network_connection::server_type;

  player_handler(server_type& server, std::uint32_t player_id);

  void add_to_game(game_handler& game_handler);

  void send(std::string message);

  [[nodiscard]] bool is_valid() const;

  void set_disconnected();

  [[nodiscard]] bool disconnected_timeouted() const;

 private:
  network_connection network_connection_;
  player_connector player_connector_;
};
