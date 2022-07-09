#include <lobby/game_request_supervisor.h>

#include <logging/logger.h>
#include <lobby/random_string.h>

game_request_supervisor::game_request_supervisor(game_handler_factory game_handler_factory,
                                                 game_handlers_map& game_handlers,
                                                 player_handlers_map& player_handlers)
    : game_handler_factory_(std::move(game_handler_factory)),
      game_handlers_(game_handlers),
      player_handlers_(player_handlers) {
}

void game_request_supervisor::create_game(std::uint32_t player_id, std::string game_hash,
                                          const std::string& scenario, const std::string& map,
                                          std::int32_t number_of_players) {
  LOG(debug) << "Creating game with game_hash: " << game_hash << ", scenario: " << scenario
             << ", map: " << map << ", number_of_players: " << number_of_players;

  if (game_hash.empty()) {
    game_hash = random_string(12);
  }

  auto& game_handler = add_game(game_hash, scenario, map, number_of_players);
  player_handlers_.at(player_id)->add_to_game(game_handler);
}

void game_request_supervisor::join_game(std::uint32_t player_id, const std::string& game_hash) {
  LOG(debug) << "Joining game with game_hash: " << game_hash;

  auto game_it = game_handlers_.find(game_hash);
  if (game_it == std::end(game_handlers_)) {
    LOG(warning) << "There is no game with requested game_hash: " << game_hash;
    // TODO: send message that game hash is invalid
    return;
  }

  auto& game_handler = game_it->second;
  if (!game_handler.is_full()) {
    player_handlers_.at(player_id)->add_to_game(game_it->second);

  } else {
    LOG(warning) << "Game with game_hash: " << game_hash << " is already full";
    // TODO: send message that game is already full
  }
}

void game_request_supervisor::find_opponent_and_create_game(std::uint32_t player_id) {
  waiting_players_.push(player_id);

  LOG(debug) << "Player with id: " << player_id << " adding to waiting player, there are: "
             << waiting_players_.size() << " waiting players.";

  while (waiting_players_.size() >= 2) {
    auto first_client_id = get_next_waiting_player();
    if (!first_client_id) {
      continue;
    }
    auto second_client_id = get_next_waiting_player();
    if (!second_client_id) {
      continue;
    }

    auto game_hash = random_string(12);

    // TODO: make map random?
    auto& game_handler = add_game(game_hash, "skirmish", "battlefield", 2);
    player_handlers_.at(*first_client_id)->add_to_game(game_handler);
    player_handlers_.at(*second_client_id)->add_to_game(game_handler);
  }
}

game_handler& game_request_supervisor::add_game(const std::string& game_hash, const std::string& scenario,
                                                const std::string& map, std::int32_t number_of_players) {
  auto& game_handler =
      game_handlers_.emplace(game_hash, game_handler_factory_.make_game_handler(
          scenario, map, number_of_players)).first->second;
  std::this_thread::sleep_for(std::chrono::seconds(1)); // maybe here is too much

  return game_handler;
}

std::optional<std::uint32_t> game_request_supervisor::get_next_waiting_player() {
  if (waiting_players_.empty()) {
    return std::nullopt;
  }

  auto player_id = waiting_players_.front();
  waiting_players_.pop();

  auto it = player_handlers_.find(player_id);
  if (it == std::end(player_handlers_) || !it->second->is_valid()) {
    return std::nullopt;
  }

  return it->first;
}
