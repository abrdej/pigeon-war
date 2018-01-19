//
// Created by abrdej on 19.01.18.
//

#ifndef PIGEONWAR_PORTAL_H
#define PIGEONWAR_PORTAL_H

#include "ability.h"

class portal final : public ability {
public:
	portal() = default;
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::teleport;
	}

private:
	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t from_index, std::uint32_t to_index);

private:
	bool used{false};
};


#endif //PIGEONWAR_PORTAL_H
