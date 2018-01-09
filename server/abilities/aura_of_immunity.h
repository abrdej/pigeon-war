//
// Created by abrdej on 09.01.18.
//

#ifndef PIGEONWAR_AURA_OF_IMMUNITY_H
#define PIGEONWAR_AURA_OF_IMMUNITY_H

#include "ability.h"
#include "per_turn_usable.h"

class aura_of_immunity : public passive_ability, per_turn_callback {
public:
	explicit aura_of_immunity(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::defender;
	}

private:
	std::size_t entity_id;
	int damage_reduction_for_friends{1};
	int damage_reduction_for_owner{3};
};


#endif //PIGEONWAR_AURA_OF_IMMUNITY_H
