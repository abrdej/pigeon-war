//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_ROBO_H
#define PIGEONWAR_ROBO_H

#include <turn_based/entity.h>
#include <turn_based/move.h>
#include <turn_based/abilities.h>
#include <pigeon_war/entities/shooter/shoot.h>
#include <pigeon_war/entities/shooter/grenade.h>

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
