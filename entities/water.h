//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WATER_H
#define PIGEONWAR_WATER_H

#include "entity.h"

struct water {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(water));
        entity_def.name = "Water";
        entity_def.health_pack.is_destructible = false;
        entity_def.health_pack.base_health = indestructible;

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::water);

        return entity_def;
    }
};

#endif //PIGEONWAR_WATER_H
