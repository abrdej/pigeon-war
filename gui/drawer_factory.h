//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_DRAWER_FACTORY_H
#define PIGEONWAR_DRAWER_FACTORY_H

#include <memory>
#include "drawable.h"
#include "entity_drawer.h"
#include "managers/types_manager.h"
#include "shooter_drawing.h"
#include "entities/shooter.h"

struct drawer_factory {

    static void initialize() {
        drawer_creators[typeid(shooter)] = make<shooter_drawer>();
    }

    static bool initialized;

    struct drawer_creator {
        drawer_creator() {
            impl = [](std::size_t entity_id) {
                return std::make_shared<entity_drawer>(entity_id);
            };
        }
        std::function<drawable::ptr_type(std::size_t)> impl;

        auto operator()(std::size_t entity_id) const {
            return impl(entity_id);
        }
    };

    template <typename T>
    static drawer_creator make() {
        drawer_creator creator;
        creator.impl = [](std::size_t entity_id) {
            return std::make_shared<T>(entity_id);
        };
        return std::move(creator);
    }

    static std::unordered_map<std::type_index, drawer_creator> drawer_creators;

    static drawable::ptr_type make_drawer_for(std::size_t entity_id) {
        if (!initialized) {
            initialize();
            initialized = true;
        }
        return drawer_creators[types_manager::component_for(entity_id)](entity_id);
    }
};

#endif //PIGEONWAR_DRAWER_FACTORY_H
