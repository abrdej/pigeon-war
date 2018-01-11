//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_BLUDGEON_H
#define PIGEONWAR_BLUDGEON_H

#include "per_turn_usable.h"
#include "straight_target_ability.h"

class bludgeon final : public straight_target_ability<1>, per_turn_usable
{
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bludgeon;
	}

private:
	void use(size_t index_on) override;

private:
	const int range = 1;
	const int damage = 6;
};

#endif //PIGEONWAR_BLUDGEON_H
