//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_ROCKET_LAUNCHER_H
#define PIGEONWAR_ROCKET_LAUNCHER_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

enum class rocket_types {
	long_range_rocket,
	explosive_mortar
};

class rocket_launcher final : public straight_target_ability<5>,
							  per_turn_usable {
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::rocket;
	}

	DEFINE_DESC(rocket_launcher, base_damage, distance_bonus, rocket_change_bonus, range)

	bool was_used() const {
		return used;
	}
	void set_used() {
		used = true;
	}

private:
	void use(std::uint32_t index_on) override;

private:
	const std::int32_t base_damage = 7;
	const std::int32_t distance_bonus = 2;
	const std::int32_t rocket_change_bonus = 3;
};

#endif //PIGEONWAR_ROCKET_LAUNCHER_H
