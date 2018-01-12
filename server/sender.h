//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_SENDER_H
#define PIGEONWAR_SENDER_H

#include <functional>
#include <SFML/Network/Packet.hpp>
#include <common/message_types.h>

struct sender {
	static std::function<void(sf::Packet)> send_fn;

	static void set_sender(const std::function<void(sf::Packet)>& fn) {
		send_fn = fn;
	}

	template <typename DataType>
	static void send(const message_types& message, const DataType& x) {
		sf::Packet packet;
		packet << message << x;
		send_fn(packet);
    }

	template <typename... DataTypes>
	static void send(const message_types& message, DataTypes&&... x) {

		sf::Packet packet;
		packet << message;

		auto packer = [&packet](auto y) {
			packet << y;
		};

		sf::Int32 tab[] = {(packer(std::forward<DataTypes>(x)), 0)...};

		send_fn(packet);
	}
};

#endif //PIGEONWAR_SENDER_H
