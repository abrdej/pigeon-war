//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include <gui/entity_drawer.h>
#include "entity.h"

struct tree {
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Tree";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::tree);

        return components;
    }
};


#endif //PIGEONWAR_TREE_H
