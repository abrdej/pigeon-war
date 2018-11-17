#include "destroyer.h"

#include <abilities/abilities.h>
#include <abilities/armor.h>
#include <abilities/blow_the_ax.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void destroyer::create(base_entity& entity)
{
    entity.name = "Destroyer";

    entity.add<health_field>(50);
    entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<blow_the_ax>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<armor>(entity.entity_id));
}
