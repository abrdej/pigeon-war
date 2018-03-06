#ifndef GRENADE_H
#define GRENADE_H

#include "path_target_ability.h"
#include <vector>

class grenade final : public path_target_ability<3>
{
public:
	grenade() = default;

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::grenade;
	}

    DEFINE_DESC_ONE(grenade, damage)

private:
	void use(std::uint32_t index_on) override;

private:
	const std::int32_t damage{12};
	bool used{false};
};

#endif