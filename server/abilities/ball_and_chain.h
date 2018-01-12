//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_BALL_AND_CHAIN_H
#define PIGEONWAR_BALL_AND_CHAIN_H

#include "per_turn_usable.h"
#include "path_target_ability.h"

class ball_and_chain : public path_target_ability<3>, protected per_turn_callback {
public:
	explicit ball_and_chain(sf::Uint64 entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::wretch;
	}

private:
	void use(sf::Uint64 index_on) override;

private:
	sf::Uint64 entity_id;
	const sf::Int32 damage_per_cost = 2;
	const sf::Int32 duration = 2;
	bool used_{false};
};


#endif //PIGEONWAR_BALL_AND_CHAIN_H
