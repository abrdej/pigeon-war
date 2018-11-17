#include "saurian.h"

#include <abilities/abilities.h>
#include <abilities/tongue_of_fire.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/modification.h>

void saurian::create(base_entity& entity)
{
    entity.name = "Saurian";

    entity.add<health_field>(35);
    entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<tongue_of_fire>(entity.entity_id));
}
