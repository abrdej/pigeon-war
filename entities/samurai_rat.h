//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SAMURAI_RAT_H
#define PIGEONWAR_SAMURAI_RAT_H

#include <abilities/dodge.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/sword_blow.h"


struct samurai_rat final
{
	static entity_definition create(size_t id) {
		entity_definition entity_def(typeid(samurai_rat));
		entity_def.name = "Samuraj";
		entity_def.health_pack.base_health = 45;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<sword_blow>());
		entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<dodge>(id));
		return entity_def;
	}
};

#endif //PIGEONWAR_SAMURAI_RAT_H
