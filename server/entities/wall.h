//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WALL_H
#define PIGEONWAR_WALL_H

#include "entity.h"

struct wall {
    static auto create(base_entity& entity)
    {
        entity.name = "Wall";

        entity.add<health_field>();

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::wall);

        return entity;
    }
};

#endif //PIGEONWAR_WALL_H
