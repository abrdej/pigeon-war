//
// Created by abrdej on 08.12.17.
//

#ifndef PIGEONWAR_LONG_RANGE_MISSILE_H
#define PIGEONWAR_LONG_RANGE_MISSILE_H

#include <straight_target_ability.h>

class long_range_missile final : public straight_target_ability<12>
{
public:

	bitmap_key get_bitmap_key() const override {
		return "long_range_missile";
	}

	//DEFINE_DESC(long_range_missile, start_damage, additional_damage)

private:
	void use(std::uint32_t index_on);
	void play_animation(std::uint32_t from_index, std::uint32_t to_index);

private:
	const std::int32_t start_damage{8};
	const std::int32_t additional_damage{2};
	bool used{false};
};

#endif //PIGEONWAR_LONG_RANGE_MISSILE_H
