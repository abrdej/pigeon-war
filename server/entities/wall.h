//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WALL_H
#define PIGEONWAR_WALL_H

#include "entity.h"

struct wall {
    static auto create(std::uint32_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Wall";

        entity.add<health_field>();

        entity.add<bitmap_field>(id, bitmap_key::wall);

        return entity;
    }
};

#endif //PIGEONWAR_WALL_H
