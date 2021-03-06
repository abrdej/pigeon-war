//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_ROBO_H
#define PIGEONWAR_ROBO_H

#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"

struct robot final
{
    static auto create(base_entity& entity)
    {
        entity.name = "Robot";

        entity.add<health_field>(45);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));


    }
};

#endif //PIGEONWAR_ROBO_H
