//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_SORCERER_H
#define PIGEONWAR_SORCERER_H

#include <abilities/prison_connection.h>
#include "entity.h"
#include "server/abilities/moveable.h"

struct sorcerer final
{
    static auto create(std::uint32_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Sorcerer";

        entity.add<health_field>(45);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<prison_connection>(id));

        entity.add<bitmap_field>(id, bitmap_key::sorcerer);

        return entity;
    }
};

#endif //PIGEONWAR_SORCERER_H
