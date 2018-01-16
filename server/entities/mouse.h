//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_MOUSE_H
#define PIGEONWAR_MOUSE_H

#include <server/abilities/poisoned_missile.h>
#include <server/abilities/long_range_missile.h>
#include <components/damage_taker.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class mouse final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Poisoner";

        entity.add<health_field>(35);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<poisoned_missile>());

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::mouse);

        return entity;
    }
};

#endif //PIGEONWAR_MOUSE_H
