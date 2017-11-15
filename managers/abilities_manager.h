#ifndef ABILITIES_MANAGER_H
#define ABILITIES_MANAGER_H

#include "managers.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"

class abilities_manager : public base_manager<abilities, abilities&>
{
public:
	using moving_manager = base_manager<moveable, moveable&>;
};

#endif