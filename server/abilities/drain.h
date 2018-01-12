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
	void use(size_t index_on) override;

private:
	const int range = 1;
	const int damage = 10;
	const int drain_amount = 4;
};

#endif