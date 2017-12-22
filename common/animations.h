//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ANIMATIONS_H
#define PIGEONWAR_ANIMATIONS_H

#include <tuple>
#include <iostream>
#include "bitmaps.h"
#include <rpc/msgpack.hpp>

enum class animation_types {
	move,
	flash_bitmap,
	change_health
};

MSGPACK_ADD_ENUM(animation_types);

struct animation_pack {
	animation_pack() = default;
	animation_pack(animation_types a, std::size_t x, std::size_t y, std::size_t z, bitmap_key k)
			: animation_type(a), btm_key(k) {

		std::get<0>(tup) = x;
		std::get<1>(tup) = y;
		std::get<2>(tup) = z;

		std::cout << std::get<0>(tup)  << "\n";
		std::cout << std::get<1>(tup)  << "\n";
		std::cout << std::get<2>(tup)  << "\n";
	}

	animation_types animation_type;

	std::tuple<std::size_t, std::size_t, std::size_t> tup;

	bitmap_key btm_key;

	MSGPACK_DEFINE_MAP(animation_type, tup, btm_key);
};

#endif //PIGEONWAR_ANIMATIONS_H
