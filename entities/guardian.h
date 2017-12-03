//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_GUARDIAN_H
#define PIGEONWAR_GUARDIAN_H

#include <abilities/spear.h>
#include <abilities/shield.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class guardian final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(guardian));
        entity_def.name = "Strażnik";
        entity_def.health_pack.base_health = 55;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<spear>(id));
        entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<shield>(id));
        return entity_def;
    }
};

#endif //PIGEONWAR_GUARDIAN_H
