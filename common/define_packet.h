//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_DEFINE_PACKET_H
#define PIGEONWAR_DEFINE_PACKET_H

#include <SFML/Network/Packet.hpp>
#include "packet_helper.h"


#define PACKET_DEFINE1(NAME, M) \
 \
inline sf::Packet& operator <<(sf::Packet& packet, const NAME& x) \
{ \
	return packet << x.M; \
} \
 \
inline sf::Packet& operator >>(sf::Packet& packet, NAME& x) \
{ \
	return packet >> x.M; \
} \


#define PACKET_DEFINE3(NAME, M1, M2, M3) \
 \
inline sf::Packet& operator <<(sf::Packet& packet, const NAME& x) \
{ \
	return packet << x.M1 << x.M2 << x.M3; \
} \
 \
inline sf::Packet& operator >>(sf::Packet& packet, NAME& x) \
{ \
	return packet >> x.M1 >> x.M2 >> x.M3; \
} \


#define PACKET_DEFINE5(NAME, M1, M2, M3, M4, M5) \
 \
inline sf::Packet& operator <<(sf::Packet& packet, const NAME& x) \
{ \
	return packet << x.M1 << x.M2 << x.M3 << x.M4 << x.M5; \
} \
 \
inline sf::Packet& operator >>(sf::Packet& packet, NAME& x) \
{ \
	return packet >> x.M1 >> x.M2 >> x.M3 >> x.M4 >> x.M5; \
} \


#define PACKET_DEFINE9(NAME, M1, M2, M3, M4, M5, M6, M7, M8, M9) \
 \
inline sf::Packet& operator <<(sf::Packet& packet, const NAME& x) \
{ \
	return packet << x.M1 << x.M2 << x.M3 << x.M4 << x.M5 << x.M6 << x.M7 << x.M8 << x.M9; \
} \
 \
inline sf::Packet& operator >>(sf::Packet& packet, NAME& x) \
{ \
	return packet >> x.M1 >> x.M2 >> x.M3 >> x.M4 >> x.M5 >> x.M6 >> x.M7 >> x.M8 >> x.M9; \
} \

#endif //PIGEONWAR_DEFINE_PACKET_H
