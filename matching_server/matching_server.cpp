#include <boost/process.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <iostream>
#include <SFML/Network/Packet.hpp>
#include "common/message_types.h"

using namespace boost::process;

int main() {

    std::int32_t matching_port = 5555;
	bool is_running = true;

    std::int32_t number_of_clients = 0;
    std::vector<std::shared_ptr<sf::TcpSocket>> clients;

    std::unordered_map<std::uint32_t, child> processes;

    std::int32_t game_port = 5556;

    sf::SocketSelector selector;
    sf::TcpListener listener;

    if (listener.listen(matching_port) != sf::Socket::Done) {
        std::cout << "Listener error\n";
    }
    selector.add(listener);

    while (is_running) {

        if (selector.wait()) {

            if (selector.isReady(listener)) {

                auto client = std::make_shared<sf::TcpSocket>();

                if (listener.accept(*client) != sf::Socket::Done) {

                    std::cout << "Error\n";

                } else {

                    ++number_of_clients;

                    clients.emplace_back(client);
                }
            }

            if (number_of_clients == 2) {

                std::cout << "create game\n";

                std::string str("./pigeonwar_server ");
                str += std::to_string(game_port);

                static std::uint32_t process_gen = 0;

                child cc(str.c_str());

                //processes.emplace(process_gen++, cc);

                sf::Packet packet;
                packet << message_types::game_server_port;
                packet << game_port;

                for (auto&& client : clients) {
                    client->send(packet);
                }

                //clients.clear();
                number_of_clients = 0;

                cc.wait();

                std::cout << "end game\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::vector<std::uint32_t> processes_to_remove;

        for (auto&& game : processes) {
            if (game.second.wait_for(std::chrono::milliseconds(50))) {
                processes_to_remove.push_back(game.first);
            }
        }
        for (auto&& game_id : processes_to_remove) {
            processes.erase(game_id);
        }
    }

    return 0;
}

