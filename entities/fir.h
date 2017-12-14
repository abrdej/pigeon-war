//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_FIR_H
#define PIGEONWAR_FIR_H

#include "entity.h"

struct fir {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(fir));
        entity_def.name = "Fir";
        entity_def.health_pack.is_destructible = false;
        entity_def.health_pack.base_health = indestructible;
        return entity_def;
    }
};

#endif //PIGEONWAR_FIR_H
