#include <turn_based/abilities.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/components/power_field.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/moveable.h>
#include <power_bullet.h>
#include <stone_skin.h>

DEFINE_ENTITY_FACTORY(golem) {
  entity.name = "Golem";

  entity.add<health_field>(60);
  // entity.add<damage_taker>();
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(3));
  abilities_ptr->add_ability(std::make_shared<power_bullet>());
  abilities_ptr->add_ability(std::make_shared<stone_skin>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(golem)
