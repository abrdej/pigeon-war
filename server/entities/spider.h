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
    static auto create(base_entity& entity)
    {
        entity.name = "Spider";

        entity.add<health_field>(45);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(4));
        abilities_ptr->add_ability(std::make_shared<jaw_spider>());
        abilities_ptr->add_ability(std::make_shared<spider_web>(entity.entity_id));
        abilities_ptr->add_ability(std::make_shared<surroundings>(entity.entity_id));

        //entity.add<bitmap_field>(entity.entity_id, bitmap_key::spider);

        return entity;
    }
};

#endif //PIGEONWAR_SPIDER_H
