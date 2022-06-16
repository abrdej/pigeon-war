#include <boost/dll/alias.hpp>

#include <abilities/abilities.h>
#include <abilities/moveable.h>
#include <components/applied_effects.h>
#include <components/modification.h>
#include <entities/entity_factory_interface.h>
#include <entities/saberhand/invisibility.h>
#include <entities/saberhand/sabers.h>

struct saberhand_factory : public entity_factory_interface {
  void create(base_entity& entity) override;
};

void saberhand_factory::create(base_entity& entity) {
  entity.name = "Saberhand";

  entity.add<health_field>(60);
  entity.add<applied_effects>();
  entity.add<modification>();

  auto abilities_ptr = entity.add<abilities>();
  abilities_ptr->add_ability(std::make_shared<moveable>(4));
  abilities_ptr->add_ability(std::make_shared<sabers>(entity.entity_id));
  abilities_ptr->add_ability(std::make_shared<invisibility>(entity.entity_id));
}

entity_factory_interface_ptr create_saberhand_factory() {
  return std::make_shared<saberhand_factory>();
}

BOOST_DLL_ALIAS(
    create_saberhand_factory,
    saberhand
)
