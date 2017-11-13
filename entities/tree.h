//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_TREE_H
#define PIGEONWAR_TREE_H

#include "entity.h"

struct tree {
    static entity_data create()
    {
        entity_data data(typeid(tree));
        data.name = "Drzewo";
        data.health = indestructible;
        return data;
    }
};


#endif //PIGEONWAR_TREE_H
