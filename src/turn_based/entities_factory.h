#pragma once

#include <memory>
#include <string>

#include <turn_based/defs.h>

/**
 * @brief Entities factory.
 */
class entities_factory {
 public:
  entities_factory();
  ~entities_factory();
  entity_id_t create(const std::string& entity_name);

 private:
  struct pimpl;
  std::unique_ptr<pimpl> pimpl_;
};
