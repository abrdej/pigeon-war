#include <lobby/game_handler.h>

game_handler::game_handler(const boost::filesystem::path& game_exec_file, std::int32_t port,
                           const std::string& scenario, const std::string& map)
    : game_process_(game_exec_file,
                    std::to_string(port),
                    scenario,
                    map,
                    boost::process::std_out > stdout,
                    boost::process::std_err > stderr,
                    boost::process::std_in < stdin),
      port_(port) {
}

bool game_handler::is_valid() const {
  return !players_.empty();
}

void game_handler::add_player(std::uint32_t player_id) {
  players_.insert(player_id);
}

void game_handler::remove_player(std::uint32_t player_id) {
  players_.erase(player_id);
}
