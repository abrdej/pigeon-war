//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_LASER_H
#define PIGEONWAR_LASER_H

#include <straight_target_ability.h>
#include <turn_based/per_turn_usable.h>
#include <turn_based/turn_system.h>

class laser final : public straight_target_ability<3>,
					per_turn_usable
{
public:
	laser() = default;

	bitmap_key get_name() const override {
		return "laser";
	}

	std::string hint() const override;

	bool usable() const override {
		return !used;
	}

private:
	void use(std::uint32_t index) override;

private:
	const std::int32_t damage = 8;
	const std::int32_t bonus_damage = 2;
};

#endif //PIGEONWAR_LASER_H
