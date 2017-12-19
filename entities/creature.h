//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CREATURE_H
#define PIGEONWAR_CREATURE_H

#include <abilities/chopper.h>
#include <abilities/spiral_of_fire.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class creature final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(creature));
        entity_def.name = "Kreatura";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<chopper>(id));
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<spiral_of_fire>());

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::creature);

        return entity_def;
    }
};

#endif //PIGEONWAR_CREATURE_H
