#pragma once

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
