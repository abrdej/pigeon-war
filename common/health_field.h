//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_HEALTH_FIELD_H
#define PIGEONWAR_HEALTH_FIELD_H

#include <limits>

struct health_field {
	int health;
	int base_health;
	bool is_destructible{true};
};

static const int indestructible = std::numeric_limits<int>::max();

#endif //PIGEONWAR_HEALTH_FIELD_H
