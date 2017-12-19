#ifndef SHOOTER_H
#define SHOOTER_H

#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"

struct shooter final
{
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Shooter";
		entity_health(components).base_health = 50;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<grenade>());
		entity_directions(components) = directions::left;
		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::shooter);

//		auto components(typeid(shooter));
//		entity_name(components) = "Strzelec";
//		entity_health(components).base_health = 50;
//		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
//		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
//		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<grenade>());
//
//		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::shooter);

		return components;
	}
};

#endif