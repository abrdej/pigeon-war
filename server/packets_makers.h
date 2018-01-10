//
// Created by abrdej on 05.01.18.
//

#ifndef PIGEONWAR_PACKETS_MAKERS_H
#define PIGEONWAR_PACKETS_MAKERS_H

#include <SFML/Network/Packet.hpp>
#include "common/message_types.h"

template <typename T>
inline sf::Packet make_packet(const message_types& message, const T& x) {
	sf::Packet packet;
	packet << message << x;
	return packet;
}

#endif //PIGEONWAR_PACKETS_MAKERS_H
