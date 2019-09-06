#include <components/damage_taker.h>
#include <abilities/abilities.h>
#include "bomb_instance.h"

void bomb_instance::create(base_entity& entity) {
    entity.name = "Bomb";

    entity.add<health_field>(5);
    // entity.add<damage_taker>();

    auto abilities_ptr = entity.add<abilities>();
}

