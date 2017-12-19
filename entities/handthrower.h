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
    static auto create(size_t id)
    {
        base_components components;
        entity_name(components) = "Handthrower";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<handcannon>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<protection_field>(id));

        entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::handthrower);

        return components;
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
