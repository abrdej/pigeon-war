//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_PRISON_CONNETION_H
#define PIGEONWAR_PRISON_CONNETION_H

#include "path_target_ability.h"
#include "per_turn_usable.h"
#include <unordered_set>

class prison_connection : public path_target_ability<4>, per_turn_usable {
public:
	explicit prison_connection(sf::Uint64 entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::protection_field;
	}

private:
	void use(sf::Uint64 index_on) override;

	sf::Uint64 entity_id;
	sf::Int32 base_damage{6};
	sf::Int32 damage_per_entities_with_effect{2};
	sf::Int32 final_damage{0};
	const sf::Int32 duration{3};
	std::deque<sf::Uint64> entities_with_effect;
};


#endif //PIGEONWAR_PRISON_CONNETION_H
