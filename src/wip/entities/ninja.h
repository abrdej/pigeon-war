//
// Created by abrde on 12.12.2017.
//

#ifndef PIGEONWAR_NINJA_H
#define PIGEONWAR_NINJA_H

#include <abilities/shiruken.h>
#include <abilities/death_mark.h>
#include <turn_based/entity.h>
#include <turn_based/abilities.h>
#include <turn_based/move.h>

class ninja final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Ninja";

        entity.add<health_field>(45);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<shiruken>());
        abilities_ptr->add_ability(std::make_shared<death_mark>(entity.entity_id));


    }
};

#endif //PIGEONWAR_NINJA_H
