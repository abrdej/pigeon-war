//
// Created by abrdej on 24.01.18.
//

#ifndef PIGEONWAR_SAW_PASSING_H
#define PIGEONWAR_SAW_PASSING_H

#include <straight_target_ability.h>
#include <turn_based/per_turn_usable.h>

class saw_passing final : public straight_target_ability<5, target_types::moving, true>,
						  per_turn_usable {
public:
	explicit saw_passing(std::uint32_t entity_id);

	bitmap_key get_name() const override {
		return "mechanical_saw";
	}

	std::string hint() const override;

private:
	void use(std::uint32_t index_on) override;

private:
	std::uint32_t entity_id;
	const std::int32_t damage = 10;
};

#endif //PIGEONWAR_SAW_PASSING_H
