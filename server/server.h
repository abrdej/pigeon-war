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
#include <boost/next_prior.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <common/message_types.h>
#include "packets_makers.h"
#include "components/damage_taker.h"
#include "json.hpp"

class server {

	using json_data_type = nlohmann::json;
	using callback_type = std::function<void(json_data_type&)>;

    const std::uint32_t port;

    std::function<void(std::uint32_t)> initial_func;
	std::unordered_map<std::string, callback_type> callbacks;
	std::thread working_thread;
	std::atomic_bool is_running{false};

	sf::SocketSelector selector;
	sf::TcpListener listener;

	std::vector<std::shared_ptr<sf::TcpSocket>> clients;
	std::unordered_map<std::string, std::uint32_t> addresses;

	boost::lockfree::spsc_queue<std::pair<std::uint32_t, sf::Packet>, boost::lockfree::capacity<30>> packets_to_send;

public:
	explicit server(std::uint32_t port) : port(port) {}

    void start_listening() {
        if (listener.listen(static_cast<unsigned short>(port)) != sf::Socket::Done) {
            throw std::runtime_error("can't start listening to port: " + std::to_string(port));
        }
        selector.add(listener);
    }

	void bind(const std::string& message_type, callback_type callback) {
		callbacks.insert(std::make_pair(message_type, callback));
	};

    void set_initial_message(std::function<void(std::uint32_t client_id)> func) {
        initial_func = std::move(func);
    }

	void send_notification(const sf::Packet& packet) {
		packets_to_send.push(std::make_pair(std::numeric_limits<std::uint32_t>::max(), packet));
	}

	void send_notification_to(std::uint32_t index, sf::Packet packet) {
		packets_to_send.push(std::make_pair(index, packet));
	}

    // this is not thread safe?
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

							auto client_id = static_cast<std::uint32_t>(clients.size());

							std::cout << "New client, next id: " << client_id << "\n";
							std::cout << " remote address: " << client->getRemoteAddress().toString() << "\n";

							clients.emplace_back(client);
							selector.add(*client);

                            initial_func(client_id);
						}
					}

					for (auto&& client : clients) {
						if (selector.isReady(*client)) {

							sf::Packet request_packet;
							client->receive(request_packet);

							std::string message;
							request_packet >> message;
							json_data_type data;

                            std::cout << "message: " << message << "\n";

							try {
								data = json_data_type::parse(message);
							} catch (...) {
								std::cout << "json parse error!\n";
								std::cout << "in: " << message << "\n";
							}

							std::cout << data.dump() << "\n";

							for (auto&& callback_pack : callbacks) {
								if (data.count(callback_pack.first)) {
                                    std::cout << "call callback for message: " << callback_pack.first << "\n";
									callback_pack.second(data[callback_pack.first]);
								}
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

    void wait() {
        working_thread.join();
    }

	void close() {
		is_running = false;
		working_thread.join();
	}
};

#endif //PIGEONWAR_BINDER_H
