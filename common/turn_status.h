//
// Created by abrdej on 22.12.17.
//

#ifndef PIGEONWAR_TURN_STATUS_H
#define PIGEONWAR_TURN_STATUS_H

#include <rpc/msgpack.hpp>
#include <SFML/Network/Packet.hpp>

enum class turn_status { do_turn, wait, update };

MSGPACK_ADD_ENUM(turn_status);

inline sf::Packet& operator <<(sf::Packet& packet, const turn_status& status)
{
	int status_int = static_cast<int>(status);
	return packet << status_int;
}

inline sf::Packet& operator >>(sf::Packet& packet, turn_status& status)
{
	int status_int;
	packet >> status_int;

	status = static_cast<turn_status>(status_int);

	return packet;
}

#endif //PIGEONWAR_TURN_STATUS_H
