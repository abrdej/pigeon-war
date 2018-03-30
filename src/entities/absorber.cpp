#include "absorber.h"
#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <abilities/absorption.h>
#include <abilities/power_circle.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>

base_entity absorber::create(base_entity &entity) {
    entity.name = "Absorber";

    entity.add<health_field>(50);
    entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<absorption>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<power_circle>(entity.entity_id));

    return entity;
}