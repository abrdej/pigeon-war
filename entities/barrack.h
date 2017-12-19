//
// Created by abrdej on 22.11.17.
//

#ifndef PIGEONWAR_BARRACK_H
#define PIGEONWAR_BARRACK_H

#include "entity.h"
#include "abilities/builder.h"
#include "shooter.h"

class barrack final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Barak";
        entity_health(components).base_health = 55;
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<builder<shooter>>());
        return components;
    }
};

#endif //PIGEONWAR_BARRACK_H
