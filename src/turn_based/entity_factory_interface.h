#pragma once

#include <memory>

#include <boost/config.hpp>

#include <turn_based/entity.h>

/**
 * @brief Entity factory interface.
 */
struct BOOST_SYMBOL_VISIBLE entity_factory_interface {
  virtual void create(base_entity& entity) = 0;
  virtual ~entity_factory_interface() = default;
};

using entity_factory_interface_ptr = std::shared_ptr<entity_factory_interface>;
