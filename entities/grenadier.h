//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_GRENADIER_H
#define PIGEONWAR_GRENADIER_H

#include <abilities/poisoned_missile.h>
#include <abilities/bomb.h>
#include <abilities/detonation.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class grenadier final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(grenadier));
        entity_def.name = "Granatnik";
        entity_def.health_pack.base_health = 40;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<bomb>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<detonation>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_GRENADIER_H
