//
// Created by abrdej on 14.12.17.
//

#ifndef PIGEONWAR_ASSASSIN_SLASH_H
#define PIGEONWAR_ASSASSIN_SLASH_H

#include "ability.h"

class assassin_slash final : public ability {
public:
	explicit assassin_slash(sf::Uint64 entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::assassin_slash;
	}

private:
	void prepare(sf::Uint64 for_index);
	void set_landing(sf::Uint64 for_index);
	void use(sf::Uint64 index_on);
	void play_animation(sf::Uint64 from_index, sf::Uint64 to_index);

	const int range{5};
	const int damage{18};
	sf::Uint64 marked_target_index;
};

#endif //PIGEONWAR_ASSASSIN_SLASH_H
