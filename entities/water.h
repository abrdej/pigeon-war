//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WATER_H
#define PIGEONWAR_WATER_H

#include "entity.h"

struct water {
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Water";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::water);

        return components;
    }
};

#endif //PIGEONWAR_WATER_H
