//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_FLAME_THROWER_H
#define PIGEONWAR_FLAME_THROWER_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class flame_thrower final : public path_target_ability<4>,
							per_turn_usable
{
public:

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::flame_thrower;
	}

private:
	void use(sf::Uint64 index_on) override;

private:
	const sf::Int32 damage = 5;
	const sf::Int32 damage_bonus = 4;
	sf::Int32 counter = 0;
};


#endif //PIGEONWAR_FLAME_THROWER_H
