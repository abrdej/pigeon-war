#ifndef DRAIN_H
#define DRAIN_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class drain final : public neighboring_target_ability<>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::drain;
	}

	std::string hint() const override;
	
private:
	void use(sf::Uint64 index_on) override;

private:
	const sf::Int32 range = 1;
	const sf::Int32 damage = 10;
	const sf::Int32 drain_amount = 4;
};

#endif