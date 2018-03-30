#ifndef SHOOTER_H
#define SHOOTER_H

#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"
#include "components/damage_taker.h"
#include "components/applied_effects.h"

struct shooter final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Shooter";

		entity.add<health_field>(50);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<shoot>());
		abilities_ptr->add_ability(std::make_shared<grenade>());

		//entity.add<bitmap_field>(entity.entity_id, "shooter);

		return entity;
	}
};

#endif