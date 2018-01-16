//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDTHROWER_H
#define PIGEONWAR_HANDTHROWER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/abilities/handcannon.h"
#include "server/abilities/protection_field.h"

class handthrower final
{
public:
    static auto create(std::uint64_t id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Handthrower";

        entity.add<health_field>(45);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<handcannon>());
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<protection_field>(id));

        entity.add<bitmap_field>(id, bitmap_key::handthrower);

        return entity;
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
