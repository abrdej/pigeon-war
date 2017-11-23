//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_FISSURE_H
#define PIGEONWAR_FISSURE_H

#include "entity.h"

struct fissure {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(fissure));
        entity_def.name = "Gejzer";
        entity_def.health_pack.is_destructible = false;
        entity_def.health_pack.base_health = indestructible;
        return entity_def;
    }
};



#endif //PIGEONWAR_FISSURE_H
