#pragma once

#include <memory>

namespace create_methods {
template <typename T>
std::shared_ptr<T> make() {
  return std::make_shared<T>();
}
}  // namespace create_methods
