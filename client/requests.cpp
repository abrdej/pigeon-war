#include "requests.h"
#include "caller.h"

int get_player_id(sf::TcpSocket& socket) {

	sf::Packet packet;
	packet << "get_player_id";
	socket.send(packet);
	socket.receive(packet);

	int id;
	packet >> id;

	return id;
}

std::array<std::vector<std::size_t>, board_container::cols_n * board_container::rows_n> get_board(sf::TcpSocket& socket) {

	using ResultType = std::array<std::vector<std::size_t>, board_container::cols_n * board_container::rows_n>;

	return send_and_receive<ResultType>(socket, "get_board");
}

std::unordered_map<std::size_t, bitmap_key> get_entities_bitmaps(sf::TcpSocket& socket) {

	using ResultType = std::unordered_map<std::size_t, bitmap_key>;

	return send_and_receive<ResultType>(socket, "get_entities_bitmaps");
}

std::unordered_map<std::size_t, int> get_entities_healths(sf::TcpSocket& socket) {

	using ResultType = std::unordered_map<std::size_t, int>;

	return send_and_receive<ResultType>(socket, "get_entities_healths");
}

turn_status get_status(sf::TcpSocket& socket, int player_id) {
	return send_and_receive<turn_status>(socket, "get_status", player_id);
}

std::vector<animation_pack> pull_animations(sf::TcpSocket& socket) {
	return send_and_receive<std::vector<animation_pack>>(socket, "pull_animations");
}

game_state get_game_state(sf::TcpSocket& socket) {
	return send_and_receive<game_state>(socket, "get_game_state");
}

void call_on_button(sf::TcpSocket& socket, size_t n) {
	send_and_receive<std::string>(socket, "on_button", n);
}

void call_on_board(sf::TcpSocket& socket, size_t col, size_t row) {
//	send_and_receive<std::string>(socket, "on_board", col, row);

	sf::Packet packet;
	packet << "on_board";
	packet << col;
	packet << row;

	socket.send(packet);

	socket.receive(packet);

	std::string x;
	packet >> x;
}
