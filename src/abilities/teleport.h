//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_TELEPORT_H
#define PIGEONWAR_TELEPORT_H

#include "ability.h"

class teleport final : public active_ability
{
public:
	teleport() = default;
	bitmap_key get_bitmap_key() const override {
		return "teleport";
	}

	DEFINE_DESC_ZERO(teleport)

private:
	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t from_index, std::uint32_t to_index);

private:
	bool used{false};
};


#endif //PIGEONWAR_TELEPORT_H
