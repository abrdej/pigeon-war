//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ANIMATIONS_QUEUE_H
#define PIGEONWAR_ANIMATIONS_QUEUE_H

#include <vector>
#include <functional>
#include "common/animations.h"

struct animations_queue {

	static std::vector<animation_pack> queue;
    static std::function<void()> pull_fn;

	static void push_animation(const animation_pack& x) {
		queue.push_back(x);
	}
	static void push_animation(const animation_types& a, int x, int y, int z, bitmap_key k) {
		queue.emplace_back(a, x, y, z, k);
	}
	static std::vector<animation_pack> pull_all() {
		return std::move(queue);
	}
    static void set_pull_function(std::function<void()> fn) {
        pull_fn = fn;
    }
    static void pull() {
        pull_fn();
    }
};


#endif //PIGEONWAR_ANIMATIONS_QUEUE_H
