#pragma once

#include <abilities/ability.h>
#include <abilities/per_turn_usable.h>

class counterattack final : public passive_ability,
							per_turn_usable
{
public:
	explicit counterattack(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "counterattack";
	}

	DEFINE_DESC_ONE(counterattack, damage)

private:
	void use(std::uint32_t index_on);

private:
	const std::uint32_t entity_id;
	const std::int32_t damage{10};
};
