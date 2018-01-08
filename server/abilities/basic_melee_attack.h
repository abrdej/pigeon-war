#ifndef BASIC_MELEE_ATTACK_H
#define BASIC_MELEE_ATTACK_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class basic_melee_attack final : public neighboring_target_ability<>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::basic_melee_attack;
	}

private:
	void use(size_t index_on) override;
	void play_animation(size_t index_from, size_t index_on);
	
private:
	const int range = 1;
	const int damage = 4;
};

#endif