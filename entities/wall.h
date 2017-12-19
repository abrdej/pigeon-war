//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WALL_H
#define PIGEONWAR_WALL_H

#include "entity.h"

struct wall {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(wall));
        entity_def.name = "Wall";
        entity_def.health_pack.is_destructible = false;
        entity_def.health_pack.base_health = indestructible;

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::wall);

        return entity_def;
    }
};

#endif //PIGEONWAR_WALL_H
