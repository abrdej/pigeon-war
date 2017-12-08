//
// Created by abrdej on 08.12.17.
//

#ifndef PIGEONWAR_LONG_RANGE_MISSILE_H
#define PIGEONWAR_LONG_RANGE_MISSILE_H

#include "abilities/ability.h"
#include "core/turn.h"

class long_range_missile final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	long_range_missile();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index);

private:
	const int range{12};
	const int start_damage{8};
	const int additional_damage{2};
	bool used{false};
};

#endif //PIGEONWAR_LONG_RANGE_MISSILE_H
