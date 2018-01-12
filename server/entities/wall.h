//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WALL_H
#define PIGEONWAR_WALL_H

#include "entity.h"

struct wall {
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Wall";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::wall);

        return components;
    }
};

#endif //PIGEONWAR_WALL_H
