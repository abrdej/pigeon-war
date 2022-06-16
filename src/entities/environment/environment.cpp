#include <boost/dll/alias.hpp>

#include <components/health_field.h>
#include <entities/entity_factory_interface.h>

#define ENVIRONMENT_FACTORY_CREATOR(TYPE, NAME) \
entity_factory_interface_ptr create_##TYPE##_factory() { \
  return std::make_shared<environment_factory>(#NAME); \
}

#define ENVIRONMENT_DESTRUCTIBLE(TYPE, NAME, HEALTH) \
entity_factory_interface_ptr create_##TYPE##_factory() { \
  return std::make_shared<environment_factory>(#NAME, HEALTH); \
}

struct environment_factory : public entity_factory_interface {
  explicit environment_factory(std::string name, std::int32_t health = indestructible);
  void create(base_entity& entity) override;
  std::string name_;
  std::int32_t health_;
};

environment_factory::environment_factory(std::string name, std::int32_t health)
    : name_(std::move(name)), health_(health) {}

void environment_factory::create(base_entity& entity) {
  entity.name = name_;
  entity.add<health_field>(health_);
}

ENVIRONMENT_FACTORY_CREATOR(tree, Tree);
ENVIRONMENT_FACTORY_CREATOR(fir, Fir);
ENVIRONMENT_FACTORY_CREATOR(fire, Fire);
ENVIRONMENT_FACTORY_CREATOR(stone, Stone);
ENVIRONMENT_FACTORY_CREATOR(water, Water);

ENVIRONMENT_DESTRUCTIBLE(wall, Wall, 30);

BOOST_DLL_ALIAS(create_tree_factory, tree)
BOOST_DLL_ALIAS(create_fir_factory, fir)
BOOST_DLL_ALIAS(create_fire_factory, fire)
BOOST_DLL_ALIAS(create_stone_factory, stone)
BOOST_DLL_ALIAS(create_water_factory, water)
BOOST_DLL_ALIAS(create_wall_factory, wall)
