#include <lobby/game_handler.h>

#include <turn_based/messages/massages_makers.h>
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

bool game_handler::is_valid() const {
  return !players_.empty();
}

[[nodiscard]] bool game_handler::is_full() const {
  return players_.size() == number_of_players_;
}

void game_handler::add_player(std::uint32_t player_id) {
  players_.insert(player_id);
}

void game_handler::remove_player(std::uint32_t player_id) {
  players_.erase(player_id);
}
