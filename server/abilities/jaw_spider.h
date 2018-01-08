//
// Created by abrdej on 08.12.17.
//

#ifndef PIGEONWAR_JAW_SPIDER_H
#define PIGEONWAR_JAW_SPIDER_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class jaw_spider final : public neighboring_target_ability<>, per_turn_usable
{
public:

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::jaw_spider;
	}

	void set_used();

private:
	void use(size_t index_on) override;
	void play_animation(size_t index_on);

private:
	const int damage = 8;
	const int bonus_for_spider_web_effect = 6;
};

#endif //PIGEONWAR_JAW_SPIDER_H
