#pragma once

#include <memory>
#include <string>

class entities_factory {
 public:
  entities_factory();
  ~entities_factory();
  std::uint32_t create(const std::string& entity_name);

 private:
  struct pimpl;
  std::unique_ptr<pimpl> pimpl_;
};
