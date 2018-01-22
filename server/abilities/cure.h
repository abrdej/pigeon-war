//
// Created by abrdej on 19.01.18.
//

#ifndef PIGEONWAR_CURE_H
#define PIGEONWAR_CURE_H


#include "path_target_ability.h"
#include "per_turn_usable.h"

class cure : public path_target_ability<3, states::target_types::friendly>, per_turn_usable {
public:
	explicit cure(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::cure;
	}

private:
	void use(std::uint32_t index_on) override;

	std::uint32_t entity_id;
	std::int32_t healing_amount_per_turn{4};
	std::int32_t healing_duration{2};
	std::int32_t power_cost{6};
};


#endif //PIGEONWAR_CURE_H
