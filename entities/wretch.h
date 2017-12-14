//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class wretch final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(wretch));
        entity_def.name = "Wretch";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        return entity_def;
    }
};

#endif //PIGEONWAR_WRETCH_H
