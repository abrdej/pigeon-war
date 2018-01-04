//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_BINDER_H
#define PIGEONWAR_BINDER_H

#include <unordered_map>
#include <functional>
#include <thread>
#include <atomic>
#include <SFML/Network.hpp>
#include "json.hpp"


struct Binder {

	using json = nlohmann::json;

	std::unordered_map<std::string, std::function<json(const json&)>> callbacks;
	std::thread working_thread;
	std::atomic_bool is_running;



	void bind(const std::string& name, std::function<json(const json&)> func) {
		callbacks.insert(std::make_pair(name, func));
	}

	void start(sf::TcpSocket& socket) {

		is_running = true;

		working_thread = std::thread([this, &socket]() {

			while (is_running) {
				sf::Packet packet;
				socket.receive(packet);

				std::string json_data;
				packet >> json_data;

				json json_object = json::parse(json_data);

				std::string name = json_object["name"];

				auto result = callbacks.at(name)(json_object);

				sf::Packet result_packet;
				packet << result.dump();
				socket.send(packet);

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		});
	}

	void close() {
		is_running = false;
		working_thread.join();
	}
};

#endif //PIGEONWAR_BINDER_H
