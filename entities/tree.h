//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include "entity.h"

struct tree {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(tree));
        entity_def.name = "Drzewo";
        entity_def.health_pack.base_health = indestructible;
        return entity_def;
    }
};


#endif //PIGEONWAR_TREE_H
