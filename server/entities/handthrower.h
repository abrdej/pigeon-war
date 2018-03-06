//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDTHROWER_H
#define PIGEONWAR_HANDTHROWER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/abilities/handcannon.h"
#include "server/abilities/protection_field.h"

class handthrower final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Handthrower";

        entity.add<health_field>(45);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<handcannon>());
        abilities_ptr->add_ability(std::make_shared<protection_field>(entity.entity_id));

        return entity;
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
