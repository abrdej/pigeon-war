#pragma once

#include <limits>
#include <cstdint>

static const std::int32_t indestructible = std::numeric_limits<std::int32_t>::max();

struct health_field {
	explicit health_field(std::int32_t value)
			: health(value), base_health(value), is_destructible(true) {}

	health_field() : health(indestructible), base_health(indestructible), is_destructible(false) {}

	std::int32_t health;
	std::int32_t base_health;
	bool is_destructible;
};
