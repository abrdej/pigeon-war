//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MONK_H
#define PIGEONWAR_MONK_H

#include <abilities/magic_bullet.h>
#include <components/power_field.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"

class monk final
{
public:
    static void create(base_entity& entity)
    {
        entity.name = "Monk";

        entity.add<health_field>(45);
        entity.add<power_filed>(entity.entity_id, 10, 0);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<magic_bullet>(entity.entity_id));


    }
};

#endif //PIGEONWAR_MONK_H
