#pragma once

#include "per_turn_usable.h"
#include "path_target_ability.h"

class ball_and_chain : public path_target_ability, protected per_turn_callback {
public:
	explicit ball_and_chain(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(ball_and_chain)

private:
	void use(std::uint32_t index_on) override;

private:
	std::uint32_t entity_id;
	const std::int32_t damage_per_cost = 2;
	const std::int32_t duration = 2;
	bool used_{false};
};
