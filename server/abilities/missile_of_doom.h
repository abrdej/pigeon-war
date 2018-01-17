//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_MISSILE_OF_DOOM_H
#define PIGEONWAR_MISSILE_OF_DOOM_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class missile_of_doom final : public path_target_ability<3>, protected turn_callback_helper
{
public:
	explicit missile_of_doom(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::power_bullet;
	}

	std::string hint() const override;

private:
	void use(std::uint32_t index_on);

private:
	bool used{false};
	std::int32_t damage{10};
	std::int32_t accumulated_damage{0};
};

#endif //PIGEONWAR_MISSILE_OF_DOOM_H
