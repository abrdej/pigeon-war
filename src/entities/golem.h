#pragma once

#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/modification.h>
#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <abilities/power_bullet.h>
#include <abilities/stone_skin.h>
#include <entities/entity.h>

struct golem final
{
    static void create(base_entity& entity)
    {
        entity.name = "Golem";

        entity.add<health_field>(60);
        // entity.add<damage_taker>();
        entity.add<applied_effects>();
        entity.add<modification>();

        auto abilities_ptr = entity.add<abilities>();
        abilities_ptr->add_ability(std::make_shared<moveable>(3));
        abilities_ptr->add_ability(std::make_shared<power_bullet>());
        abilities_ptr->add_ability(std::make_shared<stone_skin>(entity.entity_id));
    }
};
