//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_BALL_AND_CHAIN_H
#define PIGEONWAR_BALL_AND_CHAIN_H

#include "per_turn_usable.h"
#include "path_target_ability.h"

class ball_and_chain : public path_target_ability<3>, protected per_turn_callback {
public:
	explicit ball_and_chain(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::wretch;
	}

private:
	void use(size_t index_on) override;

private:
	std::size_t entity_id;
	const int damage_per_cost = 2;
	const int duration = 2;
	bool used_{false};
};


#endif //PIGEONWAR_BALL_AND_CHAIN_H
