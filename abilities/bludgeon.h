//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_BLUDGEON_H
#define PIGEONWAR_BLUDGEON_H

#include <core/turn.h>
#include "ability.h"

class bludgeon final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	bludgeon();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index, size_t push_to_index);
	void refresh_usable();

private:
	static const size_t range_ = 1;
	static const size_t damage_ = 6;
	static const size_t throw_range_ = 1;
	bool used_{false};
};

#endif //PIGEONWAR_BLUDGEON_H
