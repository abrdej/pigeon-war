#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <server/abilities/drain.h>
#include <server/abilities/wolf_herd.h>
#include "entity.h"
#include "components/damage_taker.h"
#include "server/abilities/moveable.h"
#include "components/applied_effects.h"

struct werewolf final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Werewolf";

		entity.add<health_field>(60);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<drain>());
		abilities_ptr->add_ability(std::make_shared<wolf_herd>());

		//entity.add<bitmap_field>(entity.entity_id, "werewolf);

		return entity;
	}
};

#endif