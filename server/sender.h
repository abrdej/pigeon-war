//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_SENDER_H
#define PIGEONWAR_SENDER_H

#include <functional>
#include <common/message_types.h>

struct sender {
	static std::function<void(std::string)> send_fn;

	static void set_sender(const std::function<void(std::string)>& fn) {
		send_fn = fn;
	}

//	template <typename... DataTypes>
//	static void send(const message_types& message, DataTypes&&... x) {
//
//		sf::Packet packet;
//		packet << message;
//
//		auto packer = [&packet](auto y) {
//			packet << y;
//		};
//
//		std::int32_t tab[] = {(packer(std::forward<DataTypes>(x)), 0)...};
//
//		send_fn(packet);
//	}

	static void send(const std::string& message) {
		send_fn(message);
	}
};

#endif //PIGEONWAR_SENDER_H
