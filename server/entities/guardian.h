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
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Guardian";

        entity.add<health_field>(65);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<spear>(id));
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<shield>(id));

        entity.add<bitmap_field>(id, bitmap_key::guardian);

        return entity;
    }
};

#endif //PIGEONWAR_GUARDIAN_H
