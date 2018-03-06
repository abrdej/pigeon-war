//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_GUARDIAN_H
#define PIGEONWAR_GUARDIAN_H

#include <server/abilities/spear.h>
#include <server/abilities/shield.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class guardian final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Guardian";

        entity.add<health_field>(65);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<spear>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<shield>(entity.entity_id));

        return entity;
    }
};

#endif //PIGEONWAR_GUARDIAN_H
