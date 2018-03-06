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
	explicit prison_connection(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::prison_connection;
	}

private:
	void use(std::uint32_t index_on) override;

	std::uint32_t entity_id;
	std::int32_t base_damage{6};
	std::int32_t damage_per_entities_with_effect{2};
	std::int32_t final_damage{0};
	const std::int32_t duration{3};
	std::deque<std::uint32_t> entities_with_effect;
	std::deque<turn_scoped_connection> effect_holders;
};


#endif //PIGEONWAR_PRISON_CONNETION_H
