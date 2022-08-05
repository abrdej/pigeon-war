#include <claws.h>
#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/move.h>

DEFINE_ENTITY_FACTORY(wolf) {
  entity.name = "Wolf";

  entity.add<health_field>(30);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(3));
  abilities_ptr->add_ability(std::make_shared<claws>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(wolf)
