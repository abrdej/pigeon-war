#pragma once

#include <abilities/per_turn_usable.h>
#include <abilities/straight_target_ability.h>


class shoot final : public directed_target_ability<3>,
					protected per_turn_callback
{
public:
	explicit shoot(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(bullet)

	DEFINE_DESC(shoot, damage, bullets)

	bool usable() const override {
		return bullets != 0;
	}

private:
	void use(std::uint32_t on_index) override;

private:
	const std::uint32_t entity_id;
	const std::int32_t bullets_per_turn{2};
	const std::int32_t damage{6};
	std::int32_t bullets;
};
