//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBER_H
#define PIGEONWAR_ABSORBER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include <server/abilities/moveable.h>
#include <server/abilities/absorption.h>
#include <server/abilities/power_circle.h>

class absorber final
{
public:
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Absorber";

        entity.add<health_field>(50);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<absorption>(id));
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<power_circle>(id));

        entity.add<bitmap_field>(id, bitmap_key::absorber);

        return entity;
    }
};

#endif //PIGEONWAR_ABSORBER_H
