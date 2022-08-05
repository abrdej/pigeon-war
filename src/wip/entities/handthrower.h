//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDTHROWER_H
#define PIGEONWAR_HANDTHROWER_H

#include <turn_based/entity.h>
#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <abilities/handcannon.h>
#include <abilities/protection_field.h>

class handthrower final
{
public:
    static void create(base_entity& entity)
    {
        entity.name = "Handthrower";

        entity.add<health_field>(45);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<handcannon>());
        abilities_ptr->add_ability(std::make_shared<protection_field>(entity.entity_id));
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
