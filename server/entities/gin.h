//
// Created by abrde on 28.01.2018.
//

#ifndef PIGEONWAR_GIN_H
#define PIGEONWAR_GIN_H

#include <abilities/uselessness.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/fist_of_doom.h"
#include "components/additions.h"
#include "components/damage_taker.h"

struct gin final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Gin";

        entity.add<health_field>(45);
        entity.add<power_filed_with_charging>(entity.entity_id, 0, 1);
        entity.add<damage_taker>();
        entity.add<addition>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<fist_of_doom>(entity.entity_id));
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<uselessness>(entity.entity_id));

        entity.add<bitmap_field>(entity.entity_id, bitmap_key::gin);

        return entity;
    }
};

#endif //PIGEONWAR_GIN_H
