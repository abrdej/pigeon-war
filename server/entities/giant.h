//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_GIANT_H
#define PIGEONWAR_GIANT_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/aura_of_immunity.h"
#include "abilities/giant_blow.h"
#include "abilities/giant_ram.h"

struct giant final
{
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Giant";

        entity.add<health_field>(70);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<giant_blow>());
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<giant_ram>(id));
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<aura_of_immunity>(id));

        entity.add<bitmap_field>(id, bitmap_key::giant);

        return entity;
    }
};

#endif //PIGEONWAR_GIANT_H
