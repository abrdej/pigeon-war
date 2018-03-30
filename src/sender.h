//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_SENDER_H
#define PIGEONWAR_SENDER_H

#include <functional>

struct sender {
	static std::function<void(std::string)> send_fn;

	static void set_sender(const std::function<void(std::string)>& fn) {
		send_fn = fn;
	}

	static void send(const std::string& message) {
		send_fn(message);
	}
};

#endif //PIGEONWAR_SENDER_H
