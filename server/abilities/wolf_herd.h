//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_WOLF_HERD_H
#define PIGEONWAR_WOLF_HERD_H

#include "ability.h"

class wolf_herd final : public ability {
public:
	void prepare(size_t for_index) override;
	void use(size_t index_on);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::wolf_herd;
	}

private:
	bool used{false};
	int max_number_of_wolf{2};
};


#endif //PIGEONWAR_WOLF_HERD_H
