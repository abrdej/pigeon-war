#ifndef wolf_H
#define wolf_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/basic_melee_attack.h"
#include "gui/entity_drawer.h"

class wolf final
{
public:
	static auto create(size_t id) {
		base_components components;
		entity_name(components) = "Wolf";
		entity_health(components).base_health = 30;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::wolf);

		return components;
	}
};

#endif