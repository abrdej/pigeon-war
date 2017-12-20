#ifndef SABERHAND_H
#define SABERHAND_H

#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/sabers.h"
#include "server/abilities/invisibility.h"

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

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::saberhand);

		return components;
	}
};

#endif