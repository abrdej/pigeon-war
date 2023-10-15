#include <lobby/game_request_supervisor.h>

#include <logging/logger.h>
#include <lobby/random_string.h>

void player_matcher::find_opponent(std::uint32_t player_id) {
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
  }
}

std::optional<std::uint32_t> player_matcher::get_next_waiting_player() {
//  if (waiting_players_.empty()) {
//    return std::nullopt;
//  }
//
//  auto player_id = waiting_players_.front();
//  waiting_players_.pop();
//
//  player_handler_accessor accessor;
//  if (!player_handlers_.find(accessor, player_id) || !accessor->second->is_valid()) {
//    return std::nullopt;
//  }
//
//  return accessor->first;

  return std::nullopt;
}

game_request_supervisor::game_request_supervisor(game_handler_factory game_handler_factory,
                                                 game_handlers_map& game_handlers,
                                                 const player_handlers_map& player_handlers)
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

  auto game_handler = add_game(game_hash, scenario, map, number_of_players);
  if (!game_handler) {
    // TODO: handle it in some case?
    LOG(error) << "Failed to create a game with game_hash: " << game_hash;
    return;
  }

  player_handler_accessor accessor;
  if (player_handlers_.find(accessor, player_id)) {
    accessor->second->add_to_game(*game_handler);
  } else {
    LOG(error) << "There is no player handler for id: " << player_id;
  }
}

void game_request_supervisor::join_game(std::uint32_t player_id, const std::string& game_hash) {
  LOG(debug) << "Joining game with game_hash: " << game_hash;

  std::shared_ptr<game_handler> game_handler;
  {
    game_handler_accessor accessor;
    if (!game_handlers_.find(accessor, game_hash)) {
      LOG(warning) << "There is no game with requested game_hash: " << game_hash;
      // TODO: send message that game hash is invalid
      return;
    }
    game_handler = accessor->second;
  }

  if (!game_handler->has_all_players()) {
    player_handler_accessor accessor;
    if (player_handlers_.find(accessor, player_id)) {
      accessor->second->add_to_game(*game_handler);
    } else {
      LOG(error) << "There is no player handler for id: " << player_id;
    }

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
    auto game_handler = add_game(game_hash, "skirmish", "battlefield", 2);
    if (!game_handler) {
      // TODO: handle it in some case?
      LOG(error) << "Failed to create a game with game_hash: " << game_hash;
      return;
    }

    {
      player_handler_accessor accessor;
      if (player_handlers_.find(accessor, *first_client_id)) {
        accessor->second->add_to_game(*game_handler);
      } else {
        // TODO: handle it in some case?
        LOG(error) << "There is no player handler for id: " << player_id;
      }
    }
    {
      player_handler_accessor accessor;
      if (player_handlers_.find(accessor, *second_client_id)) {
        accessor->second->add_to_game(*game_handler);
      } else {
        // TODO: handle it in some case?
        LOG(error) << "There is no player handler for id: " << player_id;
      }
    }
  }
}

std::shared_ptr<game_handler> game_request_supervisor::add_game(
    const std::string& game_hash, const std::string& scenario,
    const std::string& map, std::int32_t number_of_players) {
  game_handler_accessor accessor;
  if (!game_handlers_.emplace(accessor, game_hash,
                         game_handler_factory_.make_game_handler(scenario, map, number_of_players))) {
    LOG(error) << "Failed to crate game with game_hash: " << game_hash;
    return nullptr;
  }
  std::this_thread::sleep_for(std::chrono::seconds(1)); // maybe here is too much

  return accessor->second;
}

std::optional<std::uint32_t> game_request_supervisor::get_next_waiting_player() {
  if (waiting_players_.empty()) {
    return std::nullopt;
  }

  auto player_id = waiting_players_.front();
  waiting_players_.pop();

  player_handler_accessor accessor;
  if (!player_handlers_.find(accessor, player_id) || !accessor->second->is_valid()) {
    return std::nullopt;
  }

  return accessor->first;
}
