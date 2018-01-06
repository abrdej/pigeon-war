//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_PACKET_HELPER_H
#define PIGEONWAR_PACKET_HELPER_H

#include <SFML/Network/Packet.hpp>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"

//inline sf::Packet& operator <<(sf::Packet& packet, const size_t x)
//{
//	sf::Uint64 x_conv = x;
//	packet << x_conv;
//
//	return packet;
//}
//
//inline sf::Packet& operator >>(sf::Packet& packet, size_t& x)
//{
//	sf::Uint64 x_conv;
//	packet >> x_conv;
//
//	x = x_conv;
//
//	return packet;
//}

template <typename... TT>
inline sf::Packet& operator <<(sf::Packet& packet, const std::tuple<TT...>& x)
{
	auto get_from_tuple = [&packet](auto v) {
		packet << v;
	};

	for_each_in_tuple(x, get_from_tuple);

	return packet;
}

template <typename... TT>
inline sf::Packet& operator >>(sf::Packet& packet, std::tuple<TT...>& x)
{

	auto get_from_tuple = [&packet](auto& v) mutable {
		packet >> v;
	};

	for_each_in_tuple(x, get_from_tuple);

	return packet;
}

template <typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const std::vector<T>& x)
{
	packet << x.size();

	for (auto&& elem : x) {
		packet << elem;
	}

	return packet;
}

template <typename T>
inline sf::Packet& operator >>(sf::Packet& packet, std::vector<T>& x)
{
	std::size_t size;
	packet >> size;

	x.resize(size);

	for (auto&& elem : x) {
		packet >> elem;
	}

	return packet;
}

template <typename T, std::size_t N>
inline sf::Packet& operator <<(sf::Packet& packet, const std::array<T, N>& x)
{
	sf::Uint64 size = N;
	packet << size;

	for (auto&& elem : x) {
		packet << elem;
	}

	return packet;
}

template <typename T, std::size_t N>
inline sf::Packet& operator >>(sf::Packet& packet, std::array<T, N>& x)
{
	sf::Uint64 size;
	packet >> size;

	for (auto&& elem : x) {
		packet >> elem;
	}

	return packet;
}

template <typename T1, typename T2>
inline sf::Packet& operator <<(sf::Packet& packet, const std::pair<T1, T2>& x)
{
	packet << x.first;
	packet << x.second;

	return packet;
}

template <typename T1, typename T2>
inline sf::Packet& operator >>(sf::Packet& packet, std::pair<T1, T2>& x)
{
	packet >> x.first;
	packet >> x.second;

	return packet;
}

template <typename K, typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const std::unordered_map<K, T>& x)
{
	packet << x.size();

	for (auto&& elem : x) {
		packet << elem;
	}

	return packet;
}

template <typename K, typename T>
inline sf::Packet& operator >>(sf::Packet& packet, std::unordered_map<K, T>& x)
{
	x.clear();

	std::size_t size;
	packet >> size;

	for (std::size_t i = 0; i < size; ++i) {
		std::pair<K, T> elem;
		packet >> elem;
		x.insert(elem);
	}

	return packet;
}

template <typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const std::unordered_set<T>& x)
{
	packet << x.size();

	for (auto&& elem : x) {
		packet << elem;
	}

	return packet;
}

template <typename T>
inline sf::Packet& operator >>(sf::Packet& packet, std::unordered_set<T>& x)
{
	x.clear();

	std::size_t size;
	packet >> size;

	for (std::size_t i = 0; i < size; ++i) {
		T elem;
		packet >> elem;
		x.insert(elem);
	}

	return packet;
}

#endif //PIGEONWAR_PACKET_HELPER_H
