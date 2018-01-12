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

void call_on_button(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 n);

void call_get_button_description(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 n);

void call_on_board(sf::TcpSocket& socket, sf::Int32 player_id, sf::Uint64 col, sf::Uint64 row);

#endif //PIGEONWAR_REQUESTS_H
