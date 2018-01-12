//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ENTITY_DRAW_INFO_H
#define PIGEONWAR_ENTITY_DRAW_INFO_H

#include <common/bitmaps.h>
#include <cstdio>
#include "bitmaps.h"

struct bitmap_field {
	bitmap_field() = default;
	bitmap_field(sf::Uint64 entity_id, bitmap_key bmt_key) : entity_id(entity_id), bmt_key(bmt_key) {}
	sf::Uint64 entity_id;
	bitmap_key bmt_key;
};

#endif //PIGEONWAR_ENTITY_DRAW_INFO_H
