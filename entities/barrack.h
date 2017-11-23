//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_BARRACK_H
#define PIGEONWAR_BARRACK_H

#include "entity.h"
#include "abilities/builder.h"
#include "shooter.h"

class barrack final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(barrack));
        entity_def.name = "Barak";
        entity_def.health_pack.base_health = 55;
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<builder<shooter>>());
        return entity_def;
    }
};

#endif //PIGEONWAR_BARRACK_H
