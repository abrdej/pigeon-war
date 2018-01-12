//
// Created by abrdej on 08.12.17.
//

#ifndef PIGEONWAR_LONG_RANGE_MISSILE_H
#define PIGEONWAR_LONG_RANGE_MISSILE_H

#include "straight_target_ability.h"

class long_range_missile final : public straight_target_ability<12>
{
public:

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::long_range_missile;
	}

private:
	void use(sf::Uint64 index_on);
	void play_animation(sf::Uint64 from_index, sf::Uint64 to_index);

private:
	const sf::Int32 start_damage{8};
	const sf::Int32 additional_damage{2};
	bool used{false};
};

#endif //PIGEONWAR_LONG_RANGE_MISSILE_H
