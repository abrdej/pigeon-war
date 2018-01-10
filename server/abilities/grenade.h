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

private:
	void use(size_t index_on) override;

private:
	const int damage = 12;
	bool used_{false};
};

#endif