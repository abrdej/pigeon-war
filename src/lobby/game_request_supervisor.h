#pragma once

#include <unordered_map>
#include <string>

#include <lobby/game_handler.h>
#include <lobby/player_handler.h>

class game_request_supervisor {
  using game_handlers_map = std::unordered_map<std::string, game_handler>;
  using player_handlers_map = std::unordered_map<std::uint32_t, std::shared_ptr<player_handler>>;

 public:
  game_request_supervisor(game_handler_factory game_handler_factory,
                          game_handlers_map& game_handlers,
                          player_handlers_map& player_handlers);

  void create_game(std::uint32_t player_id, std::string game_hash,
                   const std::string& scenario, const std::string& map,
                   std::int32_t number_of_players);
  void join_game(std::uint32_t player_id, const std::string& game_hash);
  void find_opponent_and_create_game(std::uint32_t player_id);

 private:
  game_handler& add_game(const std::string& game_hash, const std::string& scenario,
                         const std::string& map, std::int32_t number_of_players);
  std::optional<std::uint32_t> get_next_waiting_player();

  game_handler_factory game_handler_factory_;
  game_handlers_map& game_handlers_;
  player_handlers_map& player_handlers_;
  std::queue<std::uint32_t> waiting_players_;
};
