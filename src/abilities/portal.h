#pragma once

#include "ability.h"
#include "per_turn_usable.h"

class portal final : public active_ability, per_turn_usable {
public:
	explicit portal(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(portal)

	bool usable() const override;

private:
	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t from_index, std::uint32_t to_index);

private:
	std::uint32_t entity_id_;
	std::int32_t power_cost_{20};
};
