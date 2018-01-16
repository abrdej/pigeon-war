//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_ROBO_H
#define PIGEONWAR_ROBO_H

#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/abilities.h"
#include "server/abilities/shoot.h"
#include "server/abilities/grenade.h"

struct robot final
{
    static auto create(std::uint32_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Robot";

        entity.add<health_field>(45);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));

        entity.add<bitmap_field>(id, bitmap_key::robot);

        return entity;
    }
};

#endif //PIGEONWAR_ROBO_H
