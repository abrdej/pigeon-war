//
// Created by abrde on 12.12.2017.
//

#ifndef PIGEONWAR_NINJA_H
#define PIGEONWAR_NINJA_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/interception.h"

class ninja final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(ninja));
        entity_def.name = "Ninja";
        entity_def.health_pack.base_health = 30;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<interception>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_NINJA_H
