#ifndef SHOOT_H
#define SHOOT_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class shoot final : public straight_target_ability<3>,
					protected per_turn_callback
{
public:
	shoot();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::shoot;
	}

	std::string hint() const override;

private:
	void use(sf::Uint64 index_on) override;

private:
	const sf::Int32 damage{6};
	const sf::Int32 bullets_n{2};
	sf::Int32 bullets;
};

#endif