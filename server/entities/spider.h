//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_H
#define PIGEONWAR_SPIDER_H

#include <server/abilities/surroundings.h>
#include <server/abilities/jaw_spider.h>
#include "entity.h"
#include "server/abilities/moveable.h"
#include "server/abilities/abilities.h"
#include "server/abilities/spider_web.h"

struct spider final
{
    static auto create(sf::Uint64 id)
    {
        base_entity entity;
        entity.entity_id = id;
        entity.name = "Spider";

        entity.add<health_field>(45);
        entity.add<damage_taker>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
        abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<jaw_spider>());
        abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<spider_web>(id));
        abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<surroundings>(id));

        entity.add<bitmap_field>(id, bitmap_key::spider);

        return entity;
    }
};

#endif //PIGEONWAR_SPIDER_H
