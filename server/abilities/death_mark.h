//
// Created by abrdej on 11.01.18.
//

#ifndef PIGEONWAR_DEATH_MARK_H
#define PIGEONWAR_DEATH_MARK_H

#include "path_target_ability.h"
#include "per_turn_usable.h"


class death_mark : public path_target_ability<3> {
public:
	explicit death_mark(std::size_t entity_id);
	~death_mark();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::assassin_slash;
	}

private:
	void use(std::size_t index_on) override;

	std::size_t entity_id;
	std::size_t enemy_id;
	int death_mark_duration{5};
	bool used{false};
	bool mark_removed{false};
};


#endif //PIGEONWAR_DEATH_MARK_H
