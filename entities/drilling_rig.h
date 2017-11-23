//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_DRILLING_RIG_H
#define PIGEONWAR_DRILLING_RIG_H

#include "entity.h"


class drilling_rig final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(drilling_rig));
        entity_def.name = "Szyb wiertniczy";
        entity_def.health_pack.base_health = 45;
        return entity_def;
    }
};

#endif //PIGEONWAR_DRILLING_RIG_H
