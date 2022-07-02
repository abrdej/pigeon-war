#include <lobby/player_handler.h>

player_handler::player_handler(server_type& server, std::uint32_t player_id)
    : server_(server), player_id_(player_id) {
  client_.on_message([this](const std::string& message) {
    server_.send_message(player_id_, message);
  });

  is_working_ = true;
  worker_ = std::thread([this]() {
    while (is_working_) {
      client_.update();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });
}

player_handler::~player_handler() {
  remove_from_game();
  is_working_ = false;
  if (worker_.joinable()) {
    worker_.join();
  }
}

void player_handler::add_to_game(game_handler& game_handler) {
  client_.connect(localhost, game_handler.get_port());
  game_handler.add_player(player_id_);
  game_handler_ = &game_handler;
}

void player_handler::send(std::string message) {
  client_.send(std::move(message));
}

bool player_handler::is_valid() const {
  return !(game_handler_ && !client_.connected());
}

void player_handler::remove_from_game() {
  if (game_handler_) {
    game_handler_->remove_player(player_id_);
    game_handler_ = nullptr;
  }
}
