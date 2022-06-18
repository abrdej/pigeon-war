#pragma once

#include <boost/dll/alias.hpp>

#include <turn_based/entity_factory_interface.h>

#define DEFINE_ENTITY_FACTORY(name)                       \
struct name##_factory : public entity_factory_interface {  \
  void create(base_entity& entity) override;               \
};                                                         \
entity_factory_interface_ptr create_##name##_factory() {   \
  return std::make_shared<name##_factory>();               \
}                                                          \
void name##_factory::create(base_entity& entity)

#define FACTORY_PLUGIN_ALIAS(name)  \
BOOST_DLL_ALIAS(create_##name##_factory, name)
