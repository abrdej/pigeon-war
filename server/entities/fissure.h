//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_FISSURE_H
#define PIGEONWAR_FISSURE_H

#include "entity.h"

struct fissure {
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Fissure";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;
        return components;
    }
};



#endif //PIGEONWAR_FISSURE_H
