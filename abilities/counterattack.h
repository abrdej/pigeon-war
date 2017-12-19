//
// Created by abrdej on 30.11.17.
//

#ifndef PIGEONWAR_COUNTERATTACK_H
#define PIGEONWAR_COUNTERATTACK_H

#include "abilities/ability.h"
#include "core/turn.h"

class counterattack final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	counterattack(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::counterattack;
	}

private:
	void prepare(size_t for_index) override {}
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index);

private:
	std::size_t entity_id;
	bool used{false};
	int damage{7};
};

#endif //PIGEONWAR_COUNTERATTACK_H
