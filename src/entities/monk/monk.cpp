#include <magic_bullet.h>
#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/components/power_field.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/move.h>

DEFINE_ENTITY_FACTORY(monk) {
  entity.name = "Monk";

  entity.description = configurable("monk").get_param<std::string>("description");
  entity.add<health_field>(45);
  entity.add<power_filed>(entity.entity_id, 10, 0);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(3));
  abilities_ptr->add_ability(std::make_shared<magic_bullet>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(monk)
