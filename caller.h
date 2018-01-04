//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_CALLER_H
#define PIGEONWAR_CALLER_H

#include <SFML/Network.hpp>


template <typename... Args>
inline void send(sf::TcpSocket& socket, const std::string& name, Args&&... args) {

	sf::Packet packet;
	packet << name;

	auto packer = [&packet](auto x) {
		packet << x;
	};

	int tab[] = {(packer(std::forward<Args>(args)), 0)...};

	socket.send(packet);
}

template <typename T, typename... Args>
inline T send_and_receive(sf::TcpSocket& socket, const std::string& name, Args&&... args) {

	sf::Packet packet;
	packet << name;

	auto packer = [&packet](auto x) {
		packet << x;
	};

	int tab[] = {(packer(std::forward<Args>(args)), 0)...};

	socket.send(packet);

	socket.receive(packet);

	T x;
	packet >> x;

	return std::move(x);
}


#endif //PIGEONWAR_CALLER_H
