//
// Created by abrdej on 19.01.18.
//

#ifndef PIGEONWAR_PORTAL_H
#define PIGEONWAR_PORTAL_H

#include "ability.h"
#include "per_turn_usable.h"

class portal final : public ability, per_turn_usable {
public:
	explicit portal(std::uint32_t entity_id);
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::portal;
	}

private:
	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t from_index, std::uint32_t to_index);

private:
	std::uint32_t entity_id;
	std::int32_t power_cost{20};
};


#endif //PIGEONWAR_PORTAL_H
