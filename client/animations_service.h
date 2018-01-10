//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_ANIMATIONS_SERVICE_H
#define PIGEONWAR_ANIMATIONS_SERVICE_H


#include <memory>
#include <unordered_map>
#include <common/animations.h>
#include <caller.h>
#include <animation/animation.h>
#include <common/game_state.h>

class game_state;

struct base_handler {
	virtual void handle(sf::Packet& packet, game_state& g_state) = 0;
};

class animations_service {

	std::unordered_map<animation_def, std::unique_ptr<base_handler>, animation_def_key_hash> services;

	static std::unique_ptr<animations_service> impl;

	static animations_service& get_instance() {
		if (!impl) {
			impl = std::make_unique<animations_service>();
			impl->initialize();
		}
		return *impl;
	}

	template <typename T>
	void add(const animation_def& animation) {
		services.emplace(animation, std::make_unique<T>());
	}

public:
	static void handle(sf::Packet& packet, game_state& g_state) {
		animation_def animation;
		unpack(packet, animation);
		get_instance().services.at(animation)->handle(packet, g_state);
	}

	void initialize();
};

#endif //PIGEONWAR_ANIMATIONS_SERVICE_H
