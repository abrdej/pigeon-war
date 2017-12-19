#ifndef SABERHAND_H
#define SABERHAND_H

#include "entities/entity.h"
#include "abilities/moveable.h"
#include "abilities/sabers.h"
#include "abilities/invisibility.h"

class saberhand final
{
public:
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Saberhand";
		entity_health(components).base_health = 60;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<sabers>());
		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<invisibility>(id));

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::saberhand);

		return components;
	}
};

#endif