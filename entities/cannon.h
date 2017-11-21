//
// Created by abrdej on 20.11.17.
//

#ifndef PIGEONWAR_CANNON_H
#define PIGEONWAR_CANNON_H

#include <abilities/shoot.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "shooter.h"

class cannon final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(cannon));
        entity_def.name = "Armata";
        entity_def.health_pack.base_health = 35;
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
        return entity_def;
    }
};

#endif //PIGEONWAR_CANNON_H
