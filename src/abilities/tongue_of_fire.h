#ifndef TONGUE_OF_FIRE_H
#define TONGUE_OF_FIRE_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class tongue_of_fire final : public path_target_ability<7>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return "tongue_of_fire";
	}
	ability_types type() const override {
		return ability_types::offensive;
	}

private:
	void use(std::uint32_t index_on) override;
private:
	const std::int32_t damage = 9;
};

#endif