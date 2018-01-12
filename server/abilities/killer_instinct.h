//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_KILLER_INSTINCT_H
#define PIGEONWAR_KILLER_INSTINCT_H

#include "path_target_ability.h"
#include "moveable.h"

class killer_instinct : public path_target_ability<7, states::target_types::moving> {
public:
	explicit killer_instinct(sf::Uint64 entity_id);
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::killer_jump;
	}

private:
	void prepare(sf::Uint64 for_index) override;
	void use(sf::Uint64 index) override;

	sf::Uint64 entity_id;
	const sf::Int32 range{7};
	bool used{false};
};


#endif //PIGEONWAR_KILLER_INSTINCT_H
