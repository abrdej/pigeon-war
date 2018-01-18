//
// Created by abrdej on 05.01.18.
//

#ifndef PIGEONWAR_PACKETS_MAKERS_H
#define PIGEONWAR_PACKETS_MAKERS_H

#include <SFML/Network/Packet.hpp>
#include "common/message_types.h"
#include "json.hpp"

template <typename T>
inline sf::Packet make_packet(const message_types& message, const T& x) {
	sf::Packet packet;
	packet << message << x;
	return packet;
}

//template <typename T>
//inline sf::Packet make_packet(const message_types& message, const T& x) {
//
//	nlohmann::json json_data = x;
//	json_data["message"] = message;
//	json_data["data"] = x;
//
//	std::vector<std::uint8_t> v_cbor = nlohmann::json::to_cbor(json_data);
//
//	sf::Packet packet;
//	packet << v_cbor;
//	return packet;
//}

#endif //PIGEONWAR_PACKETS_MAKERS_H
