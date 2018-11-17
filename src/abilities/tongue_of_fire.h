#pragma once
#include "path_target_ability.h"
#include "per_turn_usable.h"

class tongue_of_fire final : public path_target_ability<7>, per_turn_usable
{
public:
	explicit tongue_of_fire(std::uint32_t entity_id);
	BITMAP(tongue_of_fire);
	ability_types type() const override {
		return ability_types::offensive;
	}

private:
	void use(std::uint32_t index_on) override;
private:
	const std::uint32_t entity_id;
	const std::int32_t damage = 9;
};
