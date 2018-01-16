//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_WARRIOR_H
#define PIGEONWAR_WARRIOR_H

#include <server/abilities/warrior_blow.h>
#include <server/abilities/immortality.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class warrior final
{
public:
    static auto create(sf::Uint64 id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Warrior";

        entity.add<health_field>(50);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<warrior_blow>());
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<immortality>(id));

        entity.add<bitmap_field>(id, bitmap_key::warrior);

        return entity;
    }
};

#endif //PIGEONWAR_WARRIOR_H
