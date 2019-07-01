#pragma once

#include <abilities/path_target_ability.h>

class grenade final : public path_target_ability<3>
{
public:
	explicit grenade(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "grenade";
	}

	DEFINE_DESC_ONE(grenade, damage)

	bool usable() const override {
		return !used;
	}

private:
	void use(std::uint32_t on_index) override;

private:
	const std::uint32_t entity_id;
	const std::int32_t damage{12};
	bool used{false};
};
