//
// Created by abrdej on 14.12.17.
//

#ifndef PIGEONWAR_ASSASSIN_SLASH_H
#define PIGEONWAR_ASSASSIN_SLASH_H

#include "ability.h"

class assassin_slash final : public ability {
public:
	explicit assassin_slash(std::uint64_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::assassin_slash;
	}

private:
	void prepare(std::uint64_t for_index);
	void set_landing(std::uint64_t for_index);
	void use(std::uint64_t index_on);
	void play_animation(std::uint64_t from_index, std::uint64_t to_index);

	const int range{5};
	const int damage{18};
	std::uint64_t marked_target_index;
};

#endif //PIGEONWAR_ASSASSIN_SLASH_H
