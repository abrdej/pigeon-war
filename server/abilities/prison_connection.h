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
	explicit prison_connection(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::protection_field;
	}

private:
	void use(std::size_t index_on) override;

	std::size_t entity_id;
	int base_damage{6};
	int damage_per_entities_with_effect{2};
	int final_damage{0};
	const int duration{3};
	std::deque<std::size_t> entities_with_effect;
};


#endif //PIGEONWAR_PRISON_CONNETION_H
