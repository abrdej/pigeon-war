//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_FIR_H
#define PIGEONWAR_FIR_H

#include "entity.h"

struct fir {
    static auto create(sf::Uint64 id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Fir";

        entity.add<health_field>();

        entity.add<bitmap_field>(id, bitmap_key::fir);

        return entity;
    }
};

#endif //PIGEONWAR_FIR_H
