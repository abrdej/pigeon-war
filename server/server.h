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
#include <boost/lockfree/spsc_queue.hpp>
#include <common/message_types.h>
#include "packets_makers.h"
#include "components/damage_taker.h"

//auto get_bitmaps() {
//	std::unordered_map<std::uint32_t, bitmap_key> returned_map;
//	entity_manager::for_all([&returned_map](base_entity entity) {
//		returned_map.insert(std::make_pair(entity.entity_id, entity.get<bitmap_field>()->bmt_key));
//	});
//	return std::move(returned_map);
//}

auto get_names() {
	std::unordered_map<std::uint32_t, std::string> returned_map;
	entity_manager::for_all([&returned_map](base_entity entity) {
		returned_map.insert(std::make_pair(entity.entity_id, entity.name));
	});
	return std::move(returned_map);
}

struct server {

	std::unordered_map<message_types, std::function<void(sf::Packet&)>, message_types_key_hash> callbacks;
	std::thread working_thread;
	std::atomic_bool is_running;

	sf::SocketSelector selector;

	sf::TcpListener listener;

	std::vector<std::shared_ptr<sf::TcpSocket>> clients;
	std::unordered_map<std::string, std::uint32_t> addresses;

	boost::lockfree::spsc_queue<std::pair<std::uint32_t, sf::Packet>, boost::lockfree::capacity<30>> packets_to_send;

	server() {

//		if (listener.listen(443) != sf::Socket::Done) {
		if (listener.listen(5555) != sf::Socket::Done) {
			std::cout << "Listener error\n";
		}

		selector.add(listener);
	}

	void bind(const message_types& message, std::function<void(sf::Packet&)> func) {
		callbacks.insert(std::make_pair(message, func));
	};

	void send_notification(const sf::Packet& packet) {
		packets_to_send.push(std::make_pair(std::numeric_limits<std::uint32_t>::max(), packet));
	}

	void send_notification_to(std::uint32_t index, sf::Packet packet) {
		packets_to_send.push(std::make_pair(index, packet));
	}

	bool is_single_client() const {
		return clients.size() == 1;
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
							send_notification_to(client_id, make_packet(message_types::player_id, static_cast<int>(client_id)));
							send_notification_to(client_id, make_packet(message_types::board, board::fields_));
							send_notification_to(client_id, make_packet(message_types::entities_names, get_names()));
							send_notification_to(client_id, make_packet(message_types::healths, get_healths()));
						}
					}

					for (auto&& client : clients) {
						if (selector.isReady(*client)) {

							sf::Packet request_packet;
							client->receive(request_packet);

							message_types request_message;
							request_packet >> request_message;

							try {
								callbacks.at(request_message)(request_packet);

							} catch (...) {
								//std::cout << "Catch: " << request_name << "\n";
							}
						}
					}
				}

				std::pair<std::uint32_t, sf::Packet> packet_pack;

				while (packets_to_send.pop(packet_pack)) {

					if (packet_pack.first == std::numeric_limits<std::uint32_t>::max()) {
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
