//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WATER_H
#define PIGEONWAR_WATER_H

#include "entity.h"

struct water {
    static auto create(base_entity& entity)
    {
        entity.name = "Water";

        entity.add<health_field>();

        return entity;
    }
};

#endif //PIGEONWAR_WATER_H
