#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_macro.h>
#include <tongue_of_fire.h>

DEFINE_ENTITY_FACTORY(saurian) {
  entity.name = "Saurian";

  entity.add<health_field>(35);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<tongue_of_fire>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(saurian)
