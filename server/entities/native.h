#ifndef NATIVE_H
#define NATIVE_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/drain.h"
#include "server/abilities/counterattack.h"

class native final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Native";

		entity.add<health_field>(50);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<drain>());
		abilities_ptr->add_ability(std::make_shared<counterattack>(entity.entity_id));

		return entity;
	}
};

#endif