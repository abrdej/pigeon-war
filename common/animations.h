//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ANIMATIONS_H
#define PIGEONWAR_ANIMATIONS_H

#include <tuple>
#include <iostream>
#include "bitmaps.h"
#include <rpc/msgpack.hpp>
#include "add_enum.h"
#include "define_packet.h"

enum class animation_types {
	move,
	flash_bitmap,
	change_health
};

PACKET_ADD_ENUM(animation_types)

MSGPACK_ADD_ENUM(animation_types);

struct animation_pack {
	animation_pack() = default;
	animation_pack(const animation_types& a, std::size_t x, std::size_t y, std::size_t z, bitmap_key k)
			: animation_type(a), x(x), y(y), z(z), btm_key(k) {
	}

	animation_types animation_type;

	std::size_t x;
	std::size_t y;
	std::size_t z;

	bitmap_key btm_key;

	//MSGPACK_DEFINE_MAP(animation_type, tup, btm_key);
};

PACKET_DEFINE5(animation_pack, animation_type, x, y, z, btm_key)

#endif //PIGEONWAR_ANIMATIONS_H
