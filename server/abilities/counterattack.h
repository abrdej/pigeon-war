//
// Created by abrdej on 30.11.17.
//

#ifndef PIGEONWAR_COUNTERATTACK_H
#define PIGEONWAR_COUNTERATTACK_H

#include "ability.h"
#include "per_turn_usable.h"

class counterattack final : public passive_ability,
							per_turn_usable
{
public:
	counterattack(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::counterattack;
	}

	std::string hint() const override;

private:
	void use(std::uint32_t index_on);

private:
	std::uint32_t entity_id;
	std::int32_t damage{7};
};

#endif //PIGEONWAR_COUNTERATTACK_H
