//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_KILLER_INSTINCT_H
#define PIGEONWAR_KILLER_INSTINCT_H

#include "path_target_ability.h"
#include "moveable.h"

class killer_instinct : public path_target_ability<7, states::target_types::moving> {
public:
	explicit killer_instinct(std::size_t entity_id);
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::killer_jump;
	}

private:
	void prepare(size_t for_index) override;
	void use(std::size_t index) override;

	std::size_t entity_id;
	const int range{7};
	bool used{false};
};


#endif //PIGEONWAR_KILLER_INSTINCT_H
