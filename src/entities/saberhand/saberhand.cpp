#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/modification.h>
#include <turn_based/entity_factory_macro.h>
#include <invisibility.h>
#include <sabers.h>

DEFINE_ENTITY_FACTORY(saberhand) {
  entity.name = "Saberhand";

  entity.add<health_field>(60);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(4));
  abilities_ptr->add_ability(std::make_shared<sabers>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<invisibility>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(saberhand)
