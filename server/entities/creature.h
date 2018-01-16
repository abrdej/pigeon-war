//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CREATURE_H
#define PIGEONWAR_CREATURE_H

#include <server/abilities/chopper.h>
#include <server/abilities/spiral_of_fire.h>
#include <damage_taker.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class creature final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Fiery Hedgehog";

        entity.add<health_field>(50);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<chopper>(id));
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<spiral_of_fire>());

        entity.add<bitmap_field>(id, bitmap_key::creature);

        return entity;
    }
};

#endif //PIGEONWAR_CREATURE_H
