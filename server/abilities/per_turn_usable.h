//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_PER_TURN_USABLE_H
#define PIGEONWAR_PER_TURN_USABLE_H

#include <core/turn_system.h>

using per_turn_callback = turn_events_helper::every_turn_callback_helper;

class per_turn_usable : protected turn_events_helper::every_turn_callback_helper {
public:
	per_turn_usable() {
		onEveryRound([this]() {
			used = false;
		});
	}

protected:
	bool used{false};
};

#endif //PIGEONWAR_PER_TURN_USABLE_H
