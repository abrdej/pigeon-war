#pragma once

#include <vector>

#include <abilities/ability.h>
#include <abilities/per_turn_usable.h>

class sabers final : public active_ability, per_turn_usable
{
public:
	explicit sabers(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(sabers)

	DEFINE_DESC_ONE(sabers, damage)

	bool usable() const override {
		return !used;
	}

private:
	void prepare(std::uint32_t for_index) override;
	void target(std::uint32_t on);
	void use(std::uint32_t index_on);

private:
	const std::uint32_t entity_id;
	const std::int32_t range = 1;
	const std::int32_t damage = 7;
	std::vector<std::uint32_t> targets_;
};
