#ifndef SHOOTER_H
#define SHOOTER_H

#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/abilities.h"
#include "server/abilities/shoot.h"
#include "server/abilities/grenade.h"
#include "components/damage_taker.h"

struct shooter final
{
	static auto create(std::uint64_t entity_id)
	{
		base_entity entity;
		entity.entity_id = entity_id;
		entity.name = "Shooter";

		entity.add<health_field>(50);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<grenade>());

		entity.add<bitmap_field>(entity_id, bitmap_key::shooter);

		return entity;
	}
};

#endif