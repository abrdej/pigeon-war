#include <boost/dll/alias.hpp>

#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <entities/entity_factory_interface.h>
#include <entities/native/counterattack.h>
#include <entities/native/drain.h>

struct native_factory : public entity_factory_interface {
  void create(base_entity& entity) override;
};

void native_factory::create(base_entity& entity) {
  entity.name = "Native";

  entity.add<health_field>(50);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<drain>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<counterattack>(entity.entity_id));
}

entity_factory_interface_ptr create_native_factory() {
  return std::make_shared<native_factory>();
}

BOOST_DLL_ALIAS(create_native_factory, native)
