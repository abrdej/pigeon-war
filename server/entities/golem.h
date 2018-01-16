//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GOLEM_H
#define PIGEONWAR_GOLEM_H

#include <abilities/stone_skin.h>
#include <abilities/power_bullet.h>
#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/defender.h"
#include "abilities/giant_blow.h"
#include "abilities/giant_ram.h"

struct golem final
{
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Golem";

        entity.add<health_field>(60);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<power_bullet>());
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<stone_skin>(id));

        entity.add<bitmap_field>(id, bitmap_key::golem);

        return entity;
    }
};


#endif //PIGEONWAR_GOLEM_H
