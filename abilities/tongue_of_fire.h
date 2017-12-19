#ifndef TONGUE_OF_FIRE_H
#define TONGUE_OF_FIRE_H

#include "abilities/ability.h"
#include "core/turn.h"

class tongue_of_fire final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	tongue_of_fire();
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::tongue_of_fire;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_bullet_animation(size_t from_index, size_t to_index);
	void refresh_usable();
private:
	const int range = 7;
	const int damage = 9;
	bool used;
};

#endif