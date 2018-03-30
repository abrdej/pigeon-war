//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_HEALTH_FIELD_H
#define PIGEONWAR_HEALTH_FIELD_H

#include <limits>

static const std::int32_t indestructible = std::numeric_limits<std::int32_t>::max();

struct health_field {
	health_field(std::int32_t value)
			: base_health(value), health(value), is_destructible(true) {}

	health_field() : is_destructible(false), base_health(indestructible), health(indestructible) {}

	std::int32_t health;
	std::int32_t base_health;
	bool is_destructible;
};

#endif //PIGEONWAR_HEALTH_FIELD_H
