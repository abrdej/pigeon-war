#include <lobby/game_handler.h>

game_handler::game_handler(const boost::filesystem::path& game_exec_file, std::int32_t port)
    : game_process_(game_exec_file,
                    std::to_string(port),
                    boost::process::std_out > stdout,
                    boost::process::std_err > stderr,
                    boost::process::std_in < stdin),
      port_(port) {

}
