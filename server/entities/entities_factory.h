//
// Created by abrdej on 06.02.18.
//

#ifndef PIGEONWAR_ENTITIES_FACTORY_H
#define PIGEONWAR_ENTITIES_FACTORY_H

#include "entity.h"

struct entities_factory {
    static std::uint32_t create(const std::string& entity_name);
};


#endif //PIGEONWAR_ENTITIES_FACTORY_H
