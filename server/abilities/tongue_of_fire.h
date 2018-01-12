#ifndef TONGUE_OF_FIRE_H
#define TONGUE_OF_FIRE_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class tongue_of_fire final : public path_target_ability<7>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::tongue_of_fire;
	}

private:
	void use(sf::Uint64 index_on) override;
private:
	const sf::Int32 damage = 9;
};

#endif