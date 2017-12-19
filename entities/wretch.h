//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_H
#define PIGEONWAR_WRETCH_H

#include <abilities/wretch_moving.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

struct wretch final
{


    static entity_definition create(size_t id)
    {
        base_components components;
        entity_name(components) = "Wretch";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<wretch_moving>(id));
        entity_directions(components) = directions::left;

        entity_definition entity_def(typeid(wretch));
        entity_def.name = "Wretch";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<wretch_moving>(id));

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::wretch);

        return entity_def;
    }
};

#endif //PIGEONWAR_WRETCH_H
