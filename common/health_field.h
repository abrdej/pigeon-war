//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_HEALTH_FIELD_H
#define PIGEONWAR_HEALTH_FIELD_H

#include <limits>

struct health_field {
	sf::Int32 health;
	sf::Int32 base_health;
	bool is_destructible{true};
};

static const sf::Int32 indestructible = std::numeric_limits<sf::Int32>::max();

#endif //PIGEONWAR_HEALTH_FIELD_H
