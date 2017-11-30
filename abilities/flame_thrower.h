//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_FLAME_THROWER_H
#define PIGEONWAR_FLAME_THROWER_H

#include "abilities/ability.h"
#include "core/turn.h"

class flame_thrower final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	flame_thrower();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords);

private:
	static const size_t range_ = 4;
	static const size_t damage_ = 5;
	static const size_t damage_bonus = 4;
	bool used{false};
	int counter = 0;
};


#endif //PIGEONWAR_FLAME_THROWER_H
