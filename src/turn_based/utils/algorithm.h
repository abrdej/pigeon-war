#pragma once

#include <algorithm>

template <typename Container, typename ValueType>
inline void remove_erase(Container& m, const ValueType& x) {
  m.erase(std::remove(std::begin(m), std::end(m), x), std::end(m));
}

template <typename Container, typename ValueType>
bool has_value(const Container& m, const ValueType& x) {
  return std::find(std::begin(m), std::end(m), x) != std::end(m);
}

template <typename Container, typename Predicate>
bool check_if(const Container& m, Predicate p) {
  return std::find_if(std::begin(m), std::end(m), p) != std::end(m);
}
