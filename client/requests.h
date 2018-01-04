//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_REQUESTS_H
#define PIGEONWAR_REQUESTS_H

#include <SFML/Network.hpp>
#include <common/turn_status.h>
#include <common/animations.h>
#include <common/game_state.h>
#include "board_container.h"
#include "common/bitmaps.h"

int get_player_id(sf::TcpSocket& socket);

std::array<std::vector<std::size_t>, board_container::cols_n * board_container::rows_n> get_board(sf::TcpSocket& socket);

std::unordered_map<std::size_t, bitmap_key> get_entities_bitmaps(sf::TcpSocket& socket);

std::unordered_map<std::size_t, int> get_entities_healths(sf::TcpSocket& socket);

turn_status get_status(sf::TcpSocket& socket, int player_id);

std::vector<animation_pack> pull_animations(sf::TcpSocket& socket);

game_state get_game_state(sf::TcpSocket& socket);

void call_on_button(sf::TcpSocket& socket, size_t n);

void call_on_board(sf::TcpSocket& socket, size_t col, size_t row);

#endif //PIGEONWAR_REQUESTS_H
