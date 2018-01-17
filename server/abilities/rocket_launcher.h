//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_ROCKET_LAUNCHER_H
#define PIGEONWAR_ROCKET_LAUNCHER_H

#include "straight_target_ability.h"
#include "path_target_ability.h"
#include "per_turn_usable.h"

class rocket_launcher final : public ability,
							  per_turn_usable
{
	enum class rocket_types {
		long_range,
		explosive
	};

public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::rocket;
	}

	bool was_used() const {
		return used;
	}

	void change_rocket_type() {
		actual_rocket_type = (actual_rocket_type == rocket_types::long_range) ? rocket_types::explosive : rocket_types::long_range;
		has_rocket_change_bonus = true;
	}

private:
	void prepare(std::uint32_t index) override;
	void use(std::uint32_t index_on);

private:
	const std::int32_t base_damage = 7;
	const std::int32_t distance_bonus = 2;
	bool has_rocket_change_bonus{false};
	const std::int32_t rocket_change_bonus = 3;
	const std::int32_t long_range_range{5};
	const std::int32_t explosive_range{4};

	rocket_types actual_rocket_type{rocket_types::long_range};
};

#endif //PIGEONWAR_ROCKET_LAUNCHER_H
