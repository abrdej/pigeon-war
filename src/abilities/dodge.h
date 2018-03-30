//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DODGE_H
#define PIGEONWAR_DODGE_H

#include "ability.h"

class dodge final : public passive_ability
{
public:
	explicit dodge(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "dodge";
	}

	DEFINE_DESC_ONE(dodge, counter)

private:
	int counter{0};
};


#endif //PIGEONWAR_DODGE_H
