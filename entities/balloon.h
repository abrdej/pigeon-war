//
// Created by abrdej on 20.11.17.
//

#ifndef PIGEONWAR_BALLOON_H
#define PIGEONWAR_BALLOON_H

#include <abilities/build_cannon.h>
#include <abilities/build_barrack.h>
#include <abilities/builder.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "barrack.h"
#include "drilling_rig.h"

class balloon final
{
public:
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Balon";
        entity_health(components).base_health = 75;
        entity_abilities(components).add_ability(abilities::ability_types::moving,
                                                std::make_shared<moveable>(2, moveable::types::straight));
        entity_abilities(components).add_ability(abilities::ability_types::special,
                                                std::make_shared<build_cannon>());
        entity_abilities(components).add_ability(abilities::ability_types::defensive,
                                                std::make_shared<builder<barrack>>());
        entity_abilities(components).add_ability(abilities::ability_types::offensive,
                                                std::make_shared<builder<drilling_rig>>());

//        entity_abilities(components).add<builder<barrack>>();
//        entity_abilities(components).add<build_cannon>();

        return components;
    }
};

#endif //PIGEONWAR_BALLOON_H
