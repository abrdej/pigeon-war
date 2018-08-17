#pragma once

#include <algorithm>

template <typename Container, typename ValueType>
inline void remove_erase(Container& m, const ValueType& x) {
    m.erase(std::remove(std::begin(m), std::end(m), x), std::end(m));
};
