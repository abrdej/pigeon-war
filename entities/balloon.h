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
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(balloon));
        entity_def.name = "Balon";
        entity_def.health_pack.base_health = 75;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving,
                                                std::make_shared<moveable>(2, moveable::types::straight));
        entity_def.entity_abilities.add_ability(abilities::ability_types::special,
                                                std::make_shared<build_cannon>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::defensive,
                                                std::make_shared<builder<barrack>>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive,
                                                std::make_shared<builder<drilling_rig>>());

//        entity_def.entity_abilities.add<builder<barrack>>();
//        entity_def.entity_abilities.add<build_cannon>();

        return entity_def;
    }
};

#endif //PIGEONWAR_BALLOON_H
