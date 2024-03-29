//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_BLUDGEON_H
#define PIGEONWAR_BLUDGEON_H

#include <turn_based/per_turn_usable.h>
#include <straight_target_ability.h>

class bludgeon final : public straight_target_ability<1>, turn_callback_helper
{
public:
	explicit bludgeon(std::uint32_t entity_id);

	bitmap_key get_name() const override {
		return "bludgeon";
	}

private:
	void use(std::uint32_t index_on) override;

private:
	bool used{false};
	const std::int32_t range = 1;
	const std::int32_t damage = 6;
	std::int32_t rage_damage{0};
};

#endif //PIGEONWAR_BLUDGEON_H
