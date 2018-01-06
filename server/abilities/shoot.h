#ifndef SHOOT_H
#define SHOOT_H

#include "ability.h"
#include "core/turn.h"

class shoot final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	shoot();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::shoot;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(std::size_t entity_id, size_t from_index, size_t to_index);
	void refresh_usable();

private:
	const int range = 3;
	const int damage = 6;
	const int bullets_n = 2;
	int bullets;
};

#endif