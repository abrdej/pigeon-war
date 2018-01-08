//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_LASER_H
#define PIGEONWAR_LASER_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"
#include "core/turn.h"

class laser final : public straight_target_ability<3>,
					per_turn_usable
{
public:
	laser() = default;
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::laser;
	}

private:
	void use(std::size_t index) override;
	void play_animation(size_t from_index, size_t to_index);

private:
	const int damage = 8;
	const int bonus_damage = 1;
	bool used{false};
};

#endif //PIGEONWAR_LASER_H
