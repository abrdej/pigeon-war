//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_LASER_H
#define PIGEONWAR_LASER_H

#include "ability.h"
#include "core/turn.h"

class laser final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	laser();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::laser;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index);

private:
	const int range = 3;
	const int damage = 8;
	const int bonus_damage = 1;
	bool used{false};
};

#endif //PIGEONWAR_LASER_H
