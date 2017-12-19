//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WALL_H
#define PIGEONWAR_WALL_H

#include "entity.h"

struct wall {
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Wall";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::wall);

        return components;
    }
};

#endif //PIGEONWAR_WALL_H
