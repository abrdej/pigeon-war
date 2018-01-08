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
	void use(size_t index_on) override;
	void play_bullet_animation(size_t from_index, size_t to_index);
private:
	const int damage = 9;
};

#endif