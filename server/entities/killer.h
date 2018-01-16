//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILLER_H
#define PIGEONWAR_KILLER_H

#include <abilities/kill.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/killer_instinct.h"

class killer final
{
public:
    static auto create(std::uint32_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Killer";

        entity.add<health_field>(40);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<kill>());
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<killer_instinct>(id));

        entity.add<bitmap_field>(id, bitmap_key::killer);

        return entity;
    }
};

#endif //PIGEONWAR_KILLER_H
