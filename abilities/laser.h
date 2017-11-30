//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_LASER_H
#define PIGEONWAR_LASER_H

#include "abilities/ability.h"
#include "core/turn.h"

class laser final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	laser();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index);

private:
	static const size_t range_ = 3;
	static const size_t damage_ = 8;
	bool used{false};
};

#endif //PIGEONWAR_LASER_H
