#include "reaper.h"

#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <abilities/charge.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>

base_entity reaper::create(base_entity& entity) {

    entity.name = "Reaper";

    entity.add<health_field>(45);
    entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<charge>(entity.entity_id));

    return entity;
}
