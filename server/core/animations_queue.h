//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ANIMATIONS_QUEUE_H
#define PIGEONWAR_ANIMATIONS_QUEUE_H

#include <vector>
#include "common/animations.h"

struct animations_queue {
	static std::array<std::vector<animation_pack>, 2> queue;

	static void push_animation(const animation_pack& x) {
		queue[0].push_back(x);
		queue[1].push_back(x);
	}
	static void push_animation(animation_types a, std::size_t x, std::size_t y, std::size_t z, bitmap_key k) {
		queue[0].push_back(animation_pack(a, x, y, z, k));
		queue[1].push_back(animation_pack(a, x, y, z, k));
	}
	static std::vector<animation_pack> pull_all(int id) {
		return std::move(queue[id]);
	}
};


#endif //PIGEONWAR_ANIMATIONS_QUEUE_H
