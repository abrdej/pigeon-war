//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DESTROYER_H
#define PIGEONWAR_DESTROYER_H

#include <server/abilities/armor.h>
#include <server/abilities/blow_the_ax.h>
#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"

class destroyer final
{
public:
    static auto create(std::uint32_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Destroyer";

        entity.add<health_field>(50);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<blow_the_ax>());
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<armor>(id));

        entity.add<bitmap_field>(id, bitmap_key::destroyer);

        return entity;
    }
};

#endif //PIGEONWAR_DESTROYER_H
