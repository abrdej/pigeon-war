//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_DESTROYER_H
#define PIGEONWAR_DESTROYER_H

#include <abilities/abilities.h>
#include <abilities/armor.h>
#include <abilities/blow_the_ax.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <entities/entity.h>

class destroyer final
{
public:
    static auto create(base_entity& entity)
    {
        entity.name = "Destroyer";

        entity.add<health_field>(50);
        entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<blow_the_ax>());
        abilities_ptr->add_ability(std::make_shared<armor>(entity.entity_id));

        return entity;
    }
};

#endif //PIGEONWAR_DESTROYER_H