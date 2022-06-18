#pragma once

#include <memory>
#include <string>

#include <turn_based/ai/behavior_node.h>

class ai_factory {
 public:
  ai_factory();
  ~ai_factory();
  ai::behavior_node_ptr create(const std::string& ai_name);

 private:
  struct pimpl;
  std::unique_ptr<pimpl> pimpl_;
};
