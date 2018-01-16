#ifndef SABERHAND_H
#define SABERHAND_H

#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/sabers.h"
#include "server/abilities/invisibility.h"
#include "components/damage_taker.h"

class saberhand final
{
public:
	static auto create(std::uint64_t id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Saberhand";

		entity.add<health_field>(60);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<sabers>());
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<invisibility>(id));

		entity.add<bitmap_field>(id, bitmap_key::saberhand);

		return entity;
	}
};

#endif