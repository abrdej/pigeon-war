#pragma once

#include <memory>
#include <string>

class scenario_factory {
 public:
  scenario_factory();
  ~scenario_factory();
  void create(const std::string& scenario_name);

 private:
  struct pimpl;
  std::unique_ptr<pimpl> pimpl_;
};
