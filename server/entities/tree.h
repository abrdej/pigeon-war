//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include <gui/entity_drawer.h>
#include "entity.h"

struct tree {
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Tree";

        entity.add<health_field>();

        entity.add<bitmap_field>(id, bitmap_key::tree);

        return entity;
    }
};


#endif //PIGEONWAR_TREE_H
