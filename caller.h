//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_CALLER_H
#define PIGEONWAR_CALLER_H

#include <SFML/Network.hpp>
#include "common/message_types.h"


template <typename... Args>
inline void send(sf::TcpSocket& socket, const message_types& message, Args&&... args) {

	sf::Packet packet;
	packet << message;

	auto packer = [&packet](auto x) {
		packet << x;
	};

	std::int32_t tab[] = {(packer(std::forward<Args>(args)), 0)...};

	socket.send(packet);
}

template <typename T, typename... Args>
inline T send_and_receive(sf::TcpSocket& socket, const message_types& message, Args&&... args) {

	sf::Packet packet;
	packet << message;

	auto packer = [&packet](auto x) {
		packet << x;
	};

	std::int32_t tab[] = {(packer(std::forward<Args>(args)), 0)...};

	socket.send(packet);

	socket.receive(packet);

	T x;
	packet >> x;

	return std::move(x);
}

template <typename T>
inline void unpack(sf::Packet& packet, T& x) {
	packet >> x;
}


#endif //PIGEONWAR_CALLER_H
