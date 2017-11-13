#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "abilities/tongue_of_fire.h"

class saurian final
{
public:
	static entity_data create()
	{
		entity_data data(typeid(saurian));
		data.name = "Jaszczur";
		data.health = 35;
		data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());
		return data;
	}
};

#endif