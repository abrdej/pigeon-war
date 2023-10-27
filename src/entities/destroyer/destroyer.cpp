#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/entity_factory_macro.h>
#include <armor.h>
#include <blow_the_ax.h>

DEFINE_ENTITY_FACTORY(destroyer) {
  entity.name = "destroyer";

  entity.description = configurable("destroyer").get_param<std::string>("description");
  entity.add<health_field>(50);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(3));
  abilities_ptr->add_ability(std::make_shared<blow_the_ax>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<armor>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(destroyer)
