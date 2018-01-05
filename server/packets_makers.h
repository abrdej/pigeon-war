//
// Created by abrdej on 05.01.18.
//

#ifndef PIGEONWAR_PACKETS_MAKERS_H
#define PIGEONWAR_PACKETS_MAKERS_H

#include <SFML/Network/Packet.hpp>

template <typename T>
inline sf::Packet make_packet(const std::string& name, const T& x) {
	sf::Packet packet;
	packet << name << x;
	return packet;
}

#endif //PIGEONWAR_PACKETS_MAKERS_H
