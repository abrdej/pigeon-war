//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_KILLER_INSTINCT_H
#define PIGEONWAR_KILLER_INSTINCT_H

#include "path_target_ability.h"
#include "moveable.h"

class killer_instinct : public path_target_ability<7, states::target_types::moving> {
public:
	explicit killer_instinct(std::uint64_t entity_id);
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::killer_jump;
	}

private:
	void prepare(std::uint64_t for_index) override;
	void use(std::uint64_t index) override;

	std::uint64_t entity_id;
	const std::int32_t range{7};
	bool used{false};
};


#endif //PIGEONWAR_KILLER_INSTINCT_H
