//
// Created by abrdej on 22.12.17.
//

#ifndef PIGEONWAR_TURN_STATUS_H
#define PIGEONWAR_TURN_STATUS_H

#include <rpc/msgpack.hpp>

enum class turn_status { do_turn, wait, update };

MSGPACK_ADD_ENUM(turn_status);

#endif //PIGEONWAR_TURN_STATUS_H
