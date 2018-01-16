#include "requests.h"
#include "caller.h"
#include "common/message_types.h"

void call_on_button(sf::TcpSocket& socket, std::int32_t player_id, std::uint64_t n) {
	send(socket, message_types::on_button, player_id, n);
}

void call_get_button_description(sf::TcpSocket& socket, std::int32_t player_id, std::uint64_t n) {
	send(socket, message_types::get_button_description, player_id, n);
}

void call_on_board(sf::TcpSocket& socket, std::int32_t player_id, std::uint64_t col, std::uint64_t row) {

	sf::Packet packet;
	packet << message_types::on_board;
	packet << player_id;
	packet << col;
	packet << row;

	socket.send(packet);
}
