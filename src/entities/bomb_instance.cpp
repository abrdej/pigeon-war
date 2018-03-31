#include <components/damage_taker.h>
#include <abilities/abilities.h>
#include "bomb_instance.h"

base_entity bomb_instance::create(base_entity& entity) {

    entity.name = "Bomb";

    entity.add<health_field>(5);
    entity.add<damage_taker>();

    auto abilities_ptr = entity.add<abilities>();

    return entity;
}