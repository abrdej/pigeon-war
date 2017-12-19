//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDTHROWER_H
#define PIGEONWAR_HANDTHROWER_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/handcannon.h"
#include "abilities/protection_field.h"

class handthrower final
{
public:
    static entity_definition create(size_t id)
    {
        entity_definition entity_def(typeid(handthrower));
        entity_def.name = "Miotacz";
        entity_def.health_pack.base_health = 45;
        entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<handcannon>());
        entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<protection_field>(id));

        entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::handthrower);

        return entity_def;
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
