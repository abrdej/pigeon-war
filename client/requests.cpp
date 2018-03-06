#include "requests.h"
#include "caller.h"

void call_on_button(sf::TcpSocket& socket, std::int32_t client_id, std::uint32_t n) {
    using nlohmann::json;

    json inner;
    inner["client_id"] = client_id;
    inner["button"] = n;

    json data;
    data["on_button"] = inner;

    std::string message = data.dump();
    sf::Packet packet;
    packet << message;
    socket.send(packet);
}

void call_get_button_description(sf::TcpSocket& socket, std::int32_t client_id, std::uint32_t n) {
    using nlohmann::json;

    json inner;
    inner["client_id"] = client_id;
    inner["button"] = n;

    json data;
    data["get_button_description"] = inner;

    std::string message = data.dump();
    sf::Packet packet;
    packet << message;
    socket.send(packet);
}

void call_on_board(sf::TcpSocket& socket, std::int32_t client_id, std::uint32_t col, std::uint32_t row) {

    using nlohmann::json;

    json inner;
    inner["client_id"] = client_id;
    inner["col"] = col;
    inner["row"] = row;

    json data;
    data["on_board"] = inner;

	std::string message = data.dump();
	sf::Packet packet;
	packet << message;
	socket.send(packet);
}
