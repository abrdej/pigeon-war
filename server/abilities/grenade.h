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

	std::string hint() const override;


private:
	void use(sf::Uint64 index_on) override;

private:
	const sf::Int32 damage = 12;
	bool used_{false};
};

#endif