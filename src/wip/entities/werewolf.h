#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <turn_based/abilities.h>
#include <pigeon_war/entities/native/drain.h>
#include <abilities/wolf_herd.h>
#include <turn_based/entity.h>
#include <components/damage_taker.h>
#include <turn_based/moveable.h>
#include <components/applied_effects.h>

struct werewolf final
{
	static void create(base_entity& entity)
	{
		entity.name = "Werewolf";

		entity.add<health_field>(60);
		// entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<drain>());
		abilities_ptr->add_ability(std::make_shared<wolf_herd>());
	}
};

#endif