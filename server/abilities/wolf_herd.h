//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_WOLF_HERD_H
#define PIGEONWAR_WOLF_HERD_H

#include "caster_target_ability.h"

class wolf_herd final : public caster_target_ability {
public:
	void use(sf::Uint64 index_on);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::wolf_herd;
	}

private:
	bool used{false};
	sf::Int32 max_number_of_wolf{2};
};


#endif //PIGEONWAR_WOLF_HERD_H
