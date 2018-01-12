#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "server/abilities/tongue_of_fire.h"

class saurian final
{
public:
	static auto create(sf::Uint64 id)
	{
		base_components components;
		entity_name(components) = "Saurion";
		entity_health(components).base_health = 35;
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::saurian);

		return components;
	}
};

#endif