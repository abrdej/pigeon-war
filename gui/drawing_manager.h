//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_DRAWING_MANAGER_H
#define PIGEONWAR_DRAWING_MANAGER_H

#include <managers/managers.h>
#include "drawable.h"
#include "entity_drawer.h"
#include "drawer_factory.h"

struct drawing_manager : base_manager<drawable::ptr_type, drawable::ptr_type> {
    static drawable::ptr_type drawer_for(std::size_t entity_id) {
        return map_.at(entity_id);
    }

    template <typename Drawer>
    static std::shared_ptr<Drawer> typed_drawer_for(std::size_t entity_id) {
        return std::static_pointer_cast<Drawer>(map_.at(entity_id));
    }
};


#endif //PIGEONWAR_DRAWING_MANAGER_H
