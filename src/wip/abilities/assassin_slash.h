//
// Created by abrdej on 14.12.17.
//

#ifndef PIGEONWAR_ASSASSIN_SLASH_H
#define PIGEONWAR_ASSASSIN_SLASH_H

#include <turn_based/ability.h>

class assassin_slash final : public active_ability {
public:
	explicit assassin_slash(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "assassin_slash";
	}

private:
	void prepare(std::uint32_t for_index);
	void set_landing(std::uint32_t for_index);
	void use(std::uint32_t index_on);
	void play_animation(std::uint32_t from_index, std::uint32_t to_index);

	const int range{5};
	const int damage{18};
	std::uint32_t marked_target_index;
};

#endif //PIGEONWAR_ASSASSIN_SLASH_H
