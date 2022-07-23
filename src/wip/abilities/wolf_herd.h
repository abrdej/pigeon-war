//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_WOLF_HERD_H
#define PIGEONWAR_WOLF_HERD_H

#include <caster_target_ability.h>

class wolf_herd final : public caster_target_ability {
public:
	void use(std::uint32_t index_on);

	bitmap_key get_name() const override {
		return "wolf_herd";
	}

private:
	bool used{false};
	std::int32_t max_number_of_wolf{2};
};


#endif //PIGEONWAR_WOLF_HERD_H
