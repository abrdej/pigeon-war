#pragma once

#include <abilities/per_turn_usable.h>
#include <abilities/straight_target_ability.h>

enum class rocket_types {
	long_range_rocket,
	explosive_mortar
};

class rocket_launcher final : public straight_target_ability<5>,
							  per_turn_usable {
public:
	explicit rocket_launcher(std::uint32_t entity_id);
	ADD_BITMAP_GETTER(rocket)

	DEFINE_DESC(rocket_launcher, base_damage, distance_bonus, rocket_change_bonus, range)

	bool was_used() const {
		return used;
	}
	
	void set_used() {
		used = true;
	}

	bool usable() const override {
		return !used;
	}

private:
	void use(std::uint32_t on_index) override;

private:
	const std::uint32_t entity_id;
	const std::int32_t base_damage = 7;
	const std::int32_t distance_bonus = 2;
	const std::int32_t rocket_change_bonus = 3;
};
