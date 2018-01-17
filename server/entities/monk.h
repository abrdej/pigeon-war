//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MONK_H
#define PIGEONWAR_MONK_H

#include <server/abilities/magic_bullet.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class monk final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Monk";

        entity.add<health_field>(45);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<magic_bullet>(entity.entity_id));

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::monk);

        return entity;
    }
};

#endif //PIGEONWAR_MONK_H
