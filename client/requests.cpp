#include "requests.h"
#include "caller.h"
#include "common/message_types.h"

void call_on_button(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 n) {
	send(socket, message_types::on_button, player_id, n);
}

void call_get_button_description(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 n) {
	send(socket, message_types::get_button_description, player_id, n);
}

void call_on_board(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 col, sf::Uint64 row) {

	sf::Packet packet;
	packet << message_types::on_board;
	packet << player_id;
	packet << col;
	packet << row;

	socket.send(packet);
}
