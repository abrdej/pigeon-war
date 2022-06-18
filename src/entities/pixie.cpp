#include <pixie.h>

#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <abilities/poke.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>

void pixie::create(base_entity& entity) {
    entity.name = "Pixie";

    entity.add<health_field>(30);
    // entity.add<damage_taker>();
    entity.add<applied_effects>();
    entity.add<modification>();

    auto abilities_ptr = entity.add<abilities>();
    abilities_ptr->add_ability(std::make_shared<moveable>(1));
    abilities_ptr->add_ability(std::make_shared<poke>());
}
