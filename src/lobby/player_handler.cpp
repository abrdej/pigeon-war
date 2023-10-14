#include <lobby/player_handler.h>

network_connection::network_connection(server_type& server, std::int32_t client_id)
    : server_(server) {

  client_.on_message([this, client_id](const std::string& message) {
    server_.send_message(client_id, message);
  });

  is_working_ = true;
  worker_ = std::thread([this]() {
    while (is_working_) {
      client_.update();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });
}

network_connection::~network_connection() {
  is_working_ = false;
  if (worker_.joinable()) {
    worker_.join();
  }
}

void network_connection::connect_to_port(std::int32_t port) {
  client_.connect(localhost, port);
}

void network_connection::send(std::string message) {
  client_.send(std::move(message));
}

bool network_connection::is_connected() const {
  return client_.connected();
}

void network_connection::set_disconnected() {
  disconnection_time_ = std::chrono::steady_clock::now();
  disconnected_ = true;
}

bool network_connection::disconnected_timeouted() const {
  return disconnected_ && std::chrono::steady_clock::now() > disconnection_time_ + disconnection_timeout_;
}

player_connector::player_connector(std::uint32_t player_id)
    : player_id_(player_id) {
}

player_connector::~player_connector() {
  remove_from_game();
}

void player_connector::add_to_game(game_handler& game_handler) {
  game_handler.add_player(player_id_);
  game_handler_ = &game_handler;
}

void player_connector::remove_from_game() {
  if (game_handler_) {
    game_handler_->remove_player(player_id_);
    game_handler_ = nullptr;
  }
}

player_handler::player_handler(server_type& server, std::uint32_t player_id)
    : network_connection_(server, player_id), player_connector_(player_id) {
}

void player_handler::add_to_game(game_handler& game_handler) {
  network_connection_.connect_to_port(game_handler.get_port());
  player_connector_.add_to_game(game_handler);
}

void player_handler::send(std::string message) {
  network_connection_.send(std::move(message));
}

bool player_handler::is_valid() const {
  return !(player_connector_.is_valid() && !network_connection_.is_connected());
}

void player_handler::set_disconnected() {
  network_connection_.set_disconnected();
}

bool player_handler::disconnected_timeouted() const {
  return network_connection_.disconnected_timeouted();
}
