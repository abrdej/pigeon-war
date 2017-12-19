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
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Armata";
        entity_health(components).base_health = 35;
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<shoot>());
        return components;
    }
};

#endif //PIGEONWAR_CANNON_H
