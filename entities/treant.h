//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_TREANT_H
#define PIGEONWAR_TREANT_H

#include <abilities/entangling.h>
#include <abilities/recovery.h>
#include "entity.h"
#include "abilities/moveable.h"


struct treant final
{
    static entity_definition create(size_t id) {
        entity_definition entity_def(typeid(treant));
        entity_def.name = "Drzewiec";
        entity_def.health_pack.base_health = 55;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<entangling>(id));
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<recovery>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_TREANT_H
