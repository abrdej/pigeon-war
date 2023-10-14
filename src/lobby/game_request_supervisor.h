#pragma once

#include <unordered_map>
#include <string>

#include <tbb/concurrent_hash_map.h>

#include <lobby/game_handler.h>
#include <lobby/player_handler.h>

// Here we want to have:
// - players_matcher: provide ability to match opponents
// - game_request_supervisor: uses players_matcher, and creates games, adds players to game, and finds opponents.

// Provides functionality to:
// - create a game
// - add player to a game
// - find opponent and create a game

class game_request_supervisor {
  using game_handlers_map = tbb::concurrent_hash_map<std::string, std::shared_ptr<game_handler>>;
  using game_handler_accessor = game_handlers_map::accessor;

  using player_handlers_map = tbb::concurrent_hash_map<std::uint32_t, std::shared_ptr<player_handler>>;
  using player_handler_accessor = player_handlers_map::const_accessor;

 public:
  game_request_supervisor(game_handler_factory game_handler_factory,
                          game_handlers_map& game_handlers,
                          const player_handlers_map& player_handlers);

  void create_game(std::uint32_t player_id, std::string game_hash,
                   const std::string& scenario, const std::string& map,
                   std::int32_t number_of_players);
  void join_game(std::uint32_t player_id, const std::string& game_hash);
  void find_opponent_and_create_game(std::uint32_t player_id);

 private:
  std::shared_ptr<game_handler> add_game(const std::string& game_hash, const std::string& scenario,
                                         const std::string& map, std::int32_t number_of_players);
  std::optional<std::uint32_t> get_next_waiting_player();

  game_handler_factory game_handler_factory_;
  game_handlers_map& game_handlers_;
  const player_handlers_map& player_handlers_;
  std::queue<std::uint32_t> waiting_players_;
};
