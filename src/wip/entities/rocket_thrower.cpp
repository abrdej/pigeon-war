#include <rocket_thrower.h>

#include <turn_based/abilities.h>
#include <abilities/mortar_thrower.h>
#include <turn_based/move.h>
#include <abilities/rocket_launcher.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void rocket_thrower::create(base_entity& entity)
{
    entity.name = "Rocket Thrower";

    entity.add<health_field>(40);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();
    entity.add<rocket_types>(rocket_types::long_range_rocket);

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(3));
    abilities_ptr->add_ability(std::make_shared<rocket_launcher>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<mortar_thrower>(entity.entity_id));
}
