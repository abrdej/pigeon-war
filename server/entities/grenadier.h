//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_GRENADIER_H
#define PIGEONWAR_GRENADIER_H

#include <server/abilities/poisoned_missile.h>
#include <server/abilities/bomb.h>
#include <server/abilities/detonation.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class grenadier final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Grenadier";

        entity.add<health_field>(40);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<bomb>());
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<detonation>(id));

        entity.add<bitmap_field>(id, bitmap_key::grenadier);

        return entity;
    }
};

#endif //PIGEONWAR_GRENADIER_H
