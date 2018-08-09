#ifndef SHOOT_H
#define SHOOT_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class shoot final : public directed_target_ability<3>,
					protected per_turn_callback
{
public:
	shoot();

	bitmap_key get_bitmap_key() const override {
		return "bullet";
	}

	DEFINE_DESC(shoot, damage, bullets, range)

private:
	void use(std::uint32_t index_on) override;

private:
	const std::int32_t bullets_n{2};
	const std::int32_t damage{6};
	std::int32_t bullets;
};

#endif