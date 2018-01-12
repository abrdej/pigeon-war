//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include <gui/entity_drawer.h>
#include "entity.h"

struct tree {
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Tree";
        entity_health(components).is_destructible = false;
        entity_health(components).base_health = indestructible;

        entity_bitmap_field(components) = bitmap_field{id, bitmap_key::tree};

        return components;
    }
};


#endif //PIGEONWAR_TREE_H
