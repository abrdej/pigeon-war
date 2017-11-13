#ifndef SABERHAND_H
#define SABERHAND_H

#include "entities/entity.h"
#include "abilities/moveable.h"
#include "abilities/sabers.h"
#include "abilities/invisibility.h"

class saberhand final
{
public:
	static entity_data create()
	{
		entity_data data(typeid(saberhand));
		data.name = "Szablor�ki";
		data.health = 60;
		data.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		data.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<sabers>());
		data.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<invisibility>());
		return data;
	}
};

#endif