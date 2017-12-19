//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include <gui/entity_drawer.h>
#include "entity.h"

struct tree {
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(tree));
        entity_def.name = "Drzewo";
        entity_def.health_pack.is_destructible = false;
        entity_def.health_pack.base_health = indestructible;

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::tree);

        return entity_def;
    }
};


#endif //PIGEONWAR_TREE_H
