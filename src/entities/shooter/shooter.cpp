#include <grenade.h>
#include <shoot.h>
#include <turn_based/abilities.h>
#include <turn_based/board.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/components/health_field.h>
#include <turn_based/entity_factory_macro.h>
#include <turn_based/move.h>

DEFINE_ENTITY_FACTORY(shooter) {
  entity.name = "Shooter";

  LOG(debug) << "shooter_factory size: " << game_board().cols_n * game_board().rows_n;

  entity.add<health_field>(50);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<move>(4));
  abilities_ptr->add_ability(std::make_shared<shoot>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<grenade>(entity.entity_id));
}

FACTORY_PLUGIN_ALIAS(shooter)
