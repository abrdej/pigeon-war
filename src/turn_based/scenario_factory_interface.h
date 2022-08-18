#pragma once

#include <memory>

#include <boost/config.hpp>

/**
 * @brief Scenario factory interface.
 */
struct BOOST_SYMBOL_VISIBLE scenario_factory_interface {
  virtual void create() = 0;
  virtual ~scenario_factory_interface() = default;
};

using scenario_factory_interface_ptr = std::shared_ptr<scenario_factory_interface>;
