#ifndef SHOOT_H
#define SHOOT_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class shoot final : public straight_target_ability<3>,
					protected per_turn_callback
{
public:
	shoot();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::shoot;
	}

	std::string hint() const override {
		std::string desc;
		desc = "The shooter can give a double shot of: " +
				std::to_string(damage) + " damage.\n" +
				"Remaining shots: " + std::to_string(bullets) +
				"\nRange: " + std::to_string(range) + ".";
		return std::move(desc);
	}

private:
	void use(size_t index_on) override;

private:
	const int damage{6};
	const int bullets_n{2};
	int bullets;
};

#endif