#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/entity_factory_macro.h>
#include <counterattack.h>
#include <drain.h>

DEFINE_ENTITY_FACTORY(native) {
  entity.name = "Native";

  entity.add<health_field>(50);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(4));
  abilities_ptr->add_ability(std::make_shared<drain>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<counterattack>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(native)
