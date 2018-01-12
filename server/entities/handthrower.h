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
    static auto create(sf::Uint64 id)
    {
        base_components components;
        entity_name(components) = "Handthrower";
        entity_health(components).base_health = 45;
        entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
        entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<handcannon>());
        entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<protection_field>(id));

        entity_bitmap_field(components) = bitmap_field(id, bitmap_key::handthrower);

        return components;
    }
};


#endif //PIGEONWAR_HANDTHROWER_H
