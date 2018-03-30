//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_REGENERATION_H
#define PIGEONWAR_REGENERATION_H


#include <cmath>
#include "ability.h"
#include "per_turn_usable.h"


class regeneration : public passive_ability, turn_callback_helper {
public:
	explicit regeneration(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "armor";
	}

	std::string hint() const override;

private:
	std::float_t regeneration_per_factor{0.5f};
	std::uint32_t entity_id;
};

#endif //PIGEONWAR_REGENERATION_H
