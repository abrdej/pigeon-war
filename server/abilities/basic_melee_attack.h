#ifndef BASIC_MELEE_ATTACK_H
#define BASIC_MELEE_ATTACK_H

#include "ability.h"
#include "core/turn.h"

class basic_melee_attack final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	basic_melee_attack();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::basic_melee_attack;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);
	
private:
	const int range = 1;
	const int damage = 4;
	bool used{false};
};

#endif