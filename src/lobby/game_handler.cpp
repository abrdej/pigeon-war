#include <lobby/game_handler.h>

#include <logging/logger.h>
#include <turn_based/sender.h>

players_set::players_set(std::uint32_t number_of_players)
    : number_of_players_(number_of_players) {}

bool players_set::add_player(std::uint32_t player_id) {
  std::lock_guard<std::mutex> lk(mtx_);
  if (players_.size() < number_of_players_) {
    players_.insert(player_id);
    anyone_added_ = true;
    return true;
  }
  return false;
}

void players_set::remove_player(std::uint32_t player_id) {
  std::lock_guard<std::mutex> lk(mtx_);
  players_.erase(player_id);
}

bool players_set::all_players_added() const {
  std::lock_guard<std::mutex> lk(mtx_);
  return players_.size() == number_of_players_;
}

bool players_set::anyone_added() const {
  return anyone_added_;
}

std::size_t players_set::number_of_added_players() const {
  std::lock_guard<std::mutex> lk(mtx_);
  return players_.size();
}

bool players_set::has_all_players() const {
  std::lock_guard<std::mutex> lk(mtx_);
  return players_.size() == number_of_players_;
}

bool players_set::all_removed() const {
  std::lock_guard<std::mutex> lk(mtx_);
  return anyone_added_ && players_.empty();
}

game_handler::game_handler(const game_arguments& arguments)
    : players_set(arguments.number_of_players),
      executable_(make_executable(arguments.game_path,
                                  std::to_string(arguments.port),
                                  arguments.scenario,
                                  arguments.map,
                                  std::to_string(arguments.number_of_players))),
      port_(arguments.port) {
}
