//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_RAGE_H
#define PIGEONWAR_RAGE_H

#include <core/turn_system.h>
#include "abilities/ability.h"

struct rage final : public passive_ability,
					turn_events_helper::every_turn_callback_helper {

	explicit rage(std::uint32_t id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::rage;
	}

	void use();

private:
	const int range = 1;
	const int damage = 10;
	const int required_damage = 2;
	std::uint32_t damage_this_turn{0};
	std::uint32_t entity_id;
};


#endif //PIGEONWAR_RAGE_H
