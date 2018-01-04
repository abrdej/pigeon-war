#ifndef DRAIN_H
#define DRAIN_H

#include <core/turn.h>
#include "ability.h"

class drain final : public ability, turn_events_helper::every_turn_callback_helper
{
public:
	drain();
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::drain;
	}
	
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);

private:
	const int range = 1;
	const int damage = 10;
	const int drain_amount = 4;
	bool used{false};
};

#endif