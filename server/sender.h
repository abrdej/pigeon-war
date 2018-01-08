//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_SENDER_H
#define PIGEONWAR_SENDER_H

#include <functional>
#include <SFML/Network/Packet.hpp>

struct sender {
	static std::function<void(sf::Packet)> send_fn;

	static void set_sender(const std::function<void(sf::Packet)>& fn) {
		send_fn = fn;
	}

	template <typename DataType>
	static void send(const std::string& name, const DataType& x) {
		sf::Packet packet;
		packet << name << x;
		send_fn(packet);
    }
};

#endif //PIGEONWAR_SENDER_H
