//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_ADD_ENUM_H
#define PIGEONWAR_ADD_ENUM_H

#include <SFML/Network/Packet.hpp>

#define PACKET_ADD_ENUM(NAME) \
\
inline sf::Packet& operator <<(sf::Packet& packet, const NAME& enum_value) \
{ \
	int enum_int = static_cast<int>(enum_value); \
	return packet << enum_int; \
} \
\
inline sf::Packet& operator >>(sf::Packet& packet, NAME& enum_value) \
{ \
	int enum_int; \
	packet >> enum_int; \
\
	enum_value = static_cast<NAME>(enum_int); \
\
	return packet; \
} \

#endif //PIGEONWAR_ADD_ENUM_H
