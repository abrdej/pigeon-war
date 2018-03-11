//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include "entity.h"

struct tree {
    static auto create(base_entity& entity)
    {
        entity.name = "Tree";

        entity.add<health_field>();

        return entity;
    }
};


#endif //PIGEONWAR_TREE_H
