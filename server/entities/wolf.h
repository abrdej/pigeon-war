#ifndef wolf_H
#define wolf_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/abilities/basic_melee_attack.h"
#include "gui/entity_drawer.h"

class wolf final
{
public:
	static auto create(sf::Uint64 id) {
		base_components components;
		entity_name(components) = "Wolf";
		entity_health(components).base_health = 30;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::wolf);

		return components;
	}
};

#endif