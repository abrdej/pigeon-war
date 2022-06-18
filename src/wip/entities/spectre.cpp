#include <spectre.h>

#include <turn_based/abilities.h>
#include <abilities/cleaver.h>
#include <abilities/havoc.h>
#include <abilities/immateriality.h>
#include <turn_based/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/power_field.h>

void spectre::create(base_entity& entity) {
    entity.name = "Spectre";

    entity.add<health_field>(35);
    entity.add<power_filed>(entity.entity_id, 0, 0, 20);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(4));
    abilities_ptr->add_ability(std::make_shared<cleaver>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<havoc>(entity.entity_id));
    abilities_ptr->add_ability(std::make_shared<immateriality>(entity.entity_id));
}
