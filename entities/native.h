#ifndef NATIVE_H
#define NATIVE_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/drain.h"

class native final
{
public:
	static entity_data create()
	{
		entity_data data(typeid(native));
		data.name = "Tubylec";
		data.health = 50;
		//data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(0));
		data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(5));
		data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		return data;
	}
};

#endif