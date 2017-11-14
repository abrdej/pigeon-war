#ifndef SHOOTER_H
#define SHOOTER_H

#include "entity.h"

struct shooter final
{
	static entity_definition create(size_t id);
};

#endif