//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_BLUDGEON_H
#define PIGEONWAR_BLUDGEON_H

#include <core/turn.h>
#include "ability.h"

class bludgeon final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	bludgeon();
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bludgeon;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index, size_t set_on_index, size_t push_to_index);
	void refresh_usable();

private:
	const int range = 1;
	const int damage = 6;
	const int throw_range = 1;
	bool used_{false};
};

#endif //PIGEONWAR_BLUDGEON_H
