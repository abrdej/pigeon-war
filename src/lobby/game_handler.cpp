#include <lobby/game_handler.h>

#include <logging/logger.h>
#include <turn_based/sender.h>

game_handler::game_handler(const boost::filesystem::path& game_exec_file, std::int32_t port,
                           const std::string& scenario, const std::string& map, std::uint32_t number_of_players)
    : game_process_(game_exec_file,
                    std::to_string(port),
                    scenario,
                    map,
                    std::to_string(number_of_players),
                    boost::process::std_out > stdout,
                    boost::process::std_err > stderr,
                    boost::process::std_in < stdin),
      port_(port),
      number_of_players_(number_of_players) {
}

game_handler::~game_handler() {
  std::error_code ec;
  game_process_.terminate(ec);
  LOG(debug) << "terminated game with error code: " << ec.message();
}

void game_handler::start_if_full() {
  if (is_full()) {
    started_ = true;
  }
}

bool game_handler::is_invalid() const {
  std::lock_guard<std::mutex> lk(players_mtx_);
  return anyone_added_ && players_.empty();
}

[[nodiscard]] bool game_handler::is_full() const {
  std::lock_guard<std::mutex> lk(players_mtx_);
  return players_.size() == number_of_players_;
}

void game_handler::add_player(std::uint32_t player_id) {
  std::lock_guard<std::mutex> lk(players_mtx_);
  players_.insert(player_id);
  anyone_added_ = true;
}

void game_handler::remove_player(std::uint32_t player_id) {
  std::lock_guard<std::mutex> lk(players_mtx_);
  players_.erase(player_id);
}
