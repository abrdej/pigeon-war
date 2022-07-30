#pragma once

#include <cstdint>
#include <limits>
#include <ostream>

#include <type_safe/strong_typedef.hpp>

using index_t = std::uint32_t;

struct entity_id_t : type_safe::strong_typedef<entity_id_t, std::uint32_t>,
                     type_safe::strong_typedef_op::equality_comparison<entity_id_t> {
  using strong_typedef::strong_typedef;
  using value_type = decltype(value_);

  [[nodiscard]] value_type cast() const {
    return value_;
  }
};

static constexpr entity_id_t null_entity_id{std::numeric_limits<entity_id_t::value_type>::max()};

inline std::ostream& operator<<(std::ostream& out, const entity_id_t& entity_id) {
  return out << static_cast<std::uint32_t>(entity_id);
}

namespace std {

/// Hash specialization for [entity_id_t].
/// \module types
template <>
struct hash<entity_id_t> {
  std::size_t operator()(const entity_id_t& x) const noexcept {
    return std::hash<entity_id_t::value_type>()(static_cast<entity_id_t::value_type>(x));
  }
};

} // namespace std
