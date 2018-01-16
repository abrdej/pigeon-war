//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_LASER_H
#define PIGEONWAR_LASER_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"
#include "core/turn_system.h"

class laser final : public straight_target_ability<3>,
					per_turn_usable
{
public:
	laser() = default;
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::laser;
	}

	std::string hint() const override;

private:
	void use(std::uint32_t index) override;

private:
	const std::int32_t damage = 8;
	const std::int32_t bonus_damage = 1;
};

#endif //PIGEONWAR_LASER_H
