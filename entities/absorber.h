//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBER_H
#define PIGEONWAR_ABSORBER_H

#include "entity.h"
#include "abilities/abilities.h"
#include <abilities/moveable.h>
#include <abilities/absorption.h>
#include <abilities/power_circle.h>

class absorber final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(absorber));
        entity_def.name = "Absorber";
        entity_def.health_pack.base_health = 50;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<absorption>(id));
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<power_circle>(id));

        return entity_def;
    }
};

#endif //PIGEONWAR_ABSORBER_H
