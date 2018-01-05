#include "requests.h"
#include "caller.h"

void call_on_button(sf::TcpSocket& socket, int player_id, size_t n) {
	send(socket, "on_button", player_id, n);
}

void call_on_board(sf::TcpSocket& socket, int player_id, size_t col, size_t row) {

	sf::Packet packet;
	packet << "on_board";
	packet << player_id;
	packet << col;
	packet << row;

	socket.send(packet);
}
