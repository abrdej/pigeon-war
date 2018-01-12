//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_DRILLING_RIG_H
#define PIGEONWAR_DRILLING_RIG_H

#include "entity.h"


class drilling_rig final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Szyb wiertniczy";
        entity_health(components).base_health = 45;
        return components;
    }
};

#endif //PIGEONWAR_DRILLING_RIG_H
