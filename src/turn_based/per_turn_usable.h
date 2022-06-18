#pragma once

#include <turn_based/turn_system.h>

using per_turn_callback = turn_callback_helper;

class per_turn_usable : protected turn_callback_helper {
public:
	per_turn_usable() {
		on_every_two_turns_from_next([this]() {
			used = false;
		});
	}

protected:
	bool used{false};
};
