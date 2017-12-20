//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_DRAWING_MANAGER_H
#define PIGEONWAR_DRAWING_MANAGER_H

#include <common/managers.h>
#include "drawable.h"
#include "entity_drawer.h"
#include <SFML/Graphics.hpp>

struct drawing_manager : base_manager<drawable::ptr_type, drawable::ptr_type> {
    static drawable::ptr_type drawer_for(std::size_t entity_id) {
        return map_.at(entity_id);
    }

    template <typename Drawer>
    static std::shared_ptr<Drawer> typed_drawer_for(std::size_t entity_id) {
        return std::static_pointer_cast<Drawer>(map_.at(entity_id));
    }

    static bitmap_key get_bitmap_key_for(std::size_t entity_id) {
        return map_.at(entity_id)->get_bitmap_key();
    }
};

template <>
inline void add_component_of_type<drawable::ptr_type>(std::size_t entity_id, const drawable::ptr_type& component) {
    drawing_manager::add_component(entity_id, component);
}


#endif //PIGEONWAR_DRAWING_MANAGER_H
