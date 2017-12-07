//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_RAGE_H
#define PIGEONWAR_RAGE_H

#include <core/turn.h>
#include "abilities/ability.h"

struct rage final : public ability, turn_events_helper::every_turn_callback_helper {
	rage(size_t id);

	void prepare(size_t for_index) override {}
	void use();
	void play_animation(size_t use_from_index);

private:
	const int range = 1;
	const int damage = 10;
	const int required_damage = 2;
	size_t damage_this_turn{0};
	size_t entity_id;
};


#endif //PIGEONWAR_RAGE_H
