//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_FIR_H
#define PIGEONWAR_FIR_H

#include "entity.h"

struct fir {
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Fir";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::fir);

        return components;
    }
};

#endif //PIGEONWAR_FIR_H
