#pragma once

#include <string>

struct entities_factory {
  static std::uint32_t create(const std::string& entity_name);
};
