#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entities/entity.h"

class saurions_web final
{
public:
	static entity_data create()
	{
		entity_data data(typeid(saurions_web));
		data.name = "Paj�czyna jaszczura";
		data.health = 20;
		//data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());
		return data;
	}
};

#endif