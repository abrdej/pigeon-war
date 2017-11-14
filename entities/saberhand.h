#ifndef SABERHAND_H
#define SABERHAND_H

#include "entities/entity.h"
#include "abilities/moveable.h"
#include "abilities/sabers.h"
#include "abilities/invisibility.h"

class saberhand final
{
public:
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(saberhand));
		entity_def.name = "Szablor�ki";
		entity_def.health_pack.base_health = 60;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<sabers>());
		entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<invisibility>());
		return entity_def;
	}
};

#endif