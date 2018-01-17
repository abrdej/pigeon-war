//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_CHANGE_ROCKET_TYPE_H
#define PIGEONWAR_CHANGE_ROCKET_TYPE_H

#include "caster_target_ability.h"
#include "per_turn_usable.h"

class change_rocket_type final : public caster_target_ability,
								 per_turn_usable
{
public:
	explicit change_rocket_type(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::rocket;
	}

private:
	void use(std::uint32_t index_on) override;

private:
	std::uint32_t entity_id;
};

#endif //PIGEONWAR_CHANGE_ROCKET_TYPE_H
