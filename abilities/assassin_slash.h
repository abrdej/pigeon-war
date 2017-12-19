//
// Created by abrdej on 14.12.17.
//

#ifndef PIGEONWAR_ASSASSIN_SLASH_H
#define PIGEONWAR_ASSASSIN_SLASH_H

#include "abilities/ability.h"

class assassin_slash final : public ability {
public:
	explicit assassin_slash(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::assassin_slash;
	}

private:
	void prepare(size_t for_index);
	void set_landing(size_t for_index);
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index);

	const int range{5};
	const int damage{18};
	std::size_t marked_target_index;
};

#endif //PIGEONWAR_ASSASSIN_SLASH_H
