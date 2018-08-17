#ifndef BASIC_MELEE_ATTACK_H
#define BASIC_MELEE_ATTACK_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class claws final : public neighboring_target_ability<>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return "claws";
	}
	ability_types type() const override {
		return ability_types::offensive;
	}

private:
	void use(std::uint32_t index_on) override;
	
private:
	const std::int32_t range = 1;
	const std::int32_t damage = 4;
};

#endif