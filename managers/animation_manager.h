//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_ANIMATION_MANAGER_H
#define PIGEONWAR_ANIMATION_MANAGER_H

#include <cstdio>
#include <functional>
#include <queue>
#include "gui/drawing_manager.h"

using animation_type = std::function<void()>;
using animation_pack = std::pair<float, animation_type>;

struct less_for_animation_pack {
    bool operator()(const animation_pack& x, const animation_pack& y) const {
        return x.first > y.first;
    }
};

struct animation_manager {

    static std::priority_queue<animation_pack, std::vector<animation_pack>, less_for_animation_pack> animations;

    static void push_animation(const float start_time_second,
                               const animation_type& animation) {
        animations.push(std::make_pair(start_time_second, animation));
    }

    static void pull_animations() {
        sf::Clock clock;
        clock.restart();

        while (!animations.empty()) {
            auto animation = animations.top();

            if (sf::seconds(animation.first) <= clock.getElapsedTime()) {
                animation.second();
                animations.pop();
            } else {
                sf::sleep(sf::seconds(0.01));
            }
        }
    }
};

#endif //PIGEONWAR_ANIMATION_MANAGER_H
