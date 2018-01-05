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
#include <tbb/concurrent_queue.h>
#include "packets_makers.h"

struct server {

	std::unordered_map<std::string, std::function<void(sf::Packet&)>> callbacks;
	std::thread working_thread;
	std::atomic_bool is_running;

	sf::SocketSelector selector;

	sf::TcpListener listener;

	std::vector<std::shared_ptr<sf::TcpSocket>> clients;

	tbb::concurrent_queue<std::pair<std::size_t, sf::Packet>> packets_to_send;

	server() {

		if (listener.listen(8081) != sf::Socket::Done) {
			std::cout << "Listener error\n";
		}

		selector.add(listener);
	}

	void bind(const std::string& name, std::function<void(sf::Packet&)> func) {
		callbacks.insert(std::make_pair(name, func));
	};

	void send_notification(const sf::Packet& packet) {
		packets_to_send.push(std::make_pair(std::numeric_limits<std::size_t>::max(), packet));
	}

	void send_notification_to(std::size_t index, sf::Packet packet) {
		packets_to_send.push(std::make_pair(index, packet));
	}

	void start() {

		is_running = true;

		working_thread = std::thread([this]() {

			while (is_running) {

				if (selector.wait()) {

					if (selector.isReady(listener)) {

						auto client = std::make_shared<sf::TcpSocket>();

						if (listener.accept(*client) != sf::Socket::Done)
						{
							std::cout << "Error\n";

						} else {

							auto client_id = clients.size();
							std::cout << "New client, next id: " << client_id << "\n";
							std::cout << " remote address: " << client->getRemoteAddress().toString() << "\n";

							clients.emplace_back(client);
							selector.add(*client);

							// accept client and send data
							send_notification_to(client_id, make_packet("player_id", static_cast<int>(client_id)));
							send_notification_to(client_id, make_packet("board", board::fields_));
							send_notification_to(client_id, make_packet("entities_bitmaps", bitmap_field_manager::get_map()));
							send_notification_to(client_id, make_packet("healths", healths_manager::get_map()));
						}
					}

					for (auto&& client : clients) {
						if (selector.isReady(*client)) {

							sf::Packet request_packet;
							client->receive(request_packet);

							std::string request_name;
							request_packet >> request_name;

							try {
								callbacks.at(request_name)(request_packet);

							} catch (...) {
								//std::cout << "Catch: " << request_name << "\n";
							}
						}
					}
				}

				std::pair<std::size_t, sf::Packet> packet_pack;
				while (packets_to_send.try_pop(packet_pack)) {

					if (packet_pack.first == std::numeric_limits<std::size_t>::max()) {
						for (auto&& client : clients) {
							client->send(packet_pack.second);
						}
					} else {
						clients[packet_pack.first]->send(packet_pack.second);
					}
				}
			}
		});
	}

	void close() {
		is_running = false;
		working_thread.join();
	}
};

#endif //PIGEONWAR_BINDER_H