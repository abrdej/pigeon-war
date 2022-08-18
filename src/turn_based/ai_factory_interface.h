#pragma once

#include <memory>

#include <boost/config.hpp>

#include <turn_based/ai/behavior_node.h>

/**
 * @brief AI factory interface.
 */
struct BOOST_SYMBOL_VISIBLE ai_factory_interface {
  virtual ai::behavior_node_ptr create() = 0;
  virtual ~ai_factory_interface() = default;
};

using ai_factory_interface_ptr = std::shared_ptr<ai_factory_interface>;
