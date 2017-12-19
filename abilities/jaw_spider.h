//
// Created by abrdej on 08.12.17.
//

#ifndef PIGEONWAR_JAW_SPIDER_H
#define PIGEONWAR_JAW_SPIDER_H

#include "abilities/ability.h"
#include "core/turn.h"

class jaw_spider final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	jaw_spider();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::jaw_spider;
	}

	void set_used();

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t index_on);

private:
	const int range = 1;
	const int damage = 8;
	const int bonus_for_spider_web_effect = 6;
	bool used{false};
};

#endif //PIGEONWAR_JAW_SPIDER_H
