#ifndef NATIVE_H
#define NATIVE_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/drain.h"
#include "server/abilities/counterattack.h"

class native final
{
public:
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Native";
		entity_health(components).base_health = 50;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<counterattack>(id));

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::native);

		return components;
	}
};

#endif