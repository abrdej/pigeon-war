//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SAMURAI_RAT_H
#define PIGEONWAR_SAMURAI_RAT_H

#include <server/abilities/dodge.h>
#include <gui/entity_drawer.h>
#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/sword_blow.h"


struct samurai_rat final
{
	static auto create(sf::Uint64 id) {
		base_components components;
		entity_name(components) = "Samurai";
		entity_health(components).base_health = 45;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<sword_blow>());
		entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<dodge>(id));

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::samurai_rat);

		return components;
	}
};

#endif //PIGEONWAR_SAMURAI_RAT_H
