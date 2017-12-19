//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_SNIPER_H
#define PIGEONWAR_SNIPER_H

#include <abilities/hypnosis.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/sniper_shot.h"

struct sniper final
{
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(sniper));
        entity_def.name = "Sniper";
        entity_def.health_pack.base_health = 35;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<sniper_shot>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<hypnosis>());

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::sniper);

        return entity_def;
    }
};

#endif //PIGEONWAR_SNIPER_H
