//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_DRAWING_MANAGER_H
#define PIGEONWAR_DRAWING_MANAGER_H

#include <managers/managers.h>
#include "drawable.h"
#include "entity_drawer.h"

struct drawing_manager : base_manager<drawable::ptr_type, drawable::ptr_type> {
    static drawable::ptr_type drawer_for(std::size_t entity_id) {
        auto drawer = map_[entity_id];
        if (!drawer) {
            drawer = std::make_shared<entity_drawer>(entity_id);
        }
        return drawer;
    }
};


#endif //PIGEONWAR_DRAWING_MANAGER_H
