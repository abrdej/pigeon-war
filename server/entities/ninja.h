//
// Created by abrde on 12.12.2017.
//

#ifndef PIGEONWAR_NINJA_H
#define PIGEONWAR_NINJA_H

#include <server/abilities/shiruken.h>
#include <server/abilities/death_mark.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class ninja final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Ninja";

        entity.add<health_field>(45);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<shiruken>());
        abilities_ptr->add_ability(std::make_shared<death_mark>(entity.entity_id));

        return entity;
    }
};

#endif //PIGEONWAR_NINJA_H
