#pragma once

#include <cstdint>
#include <limits>
#include <ostream>

#include <type_safe/strong_typedef.hpp>

struct entity_id_t : type_safe::strong_typedef<entity_id_t, std::uint32_t>,
                     type_safe::strong_typedef_op::equality_comparison<entity_id_t> {
  using strong_typedef::strong_typedef;
  using value_type = decltype(value_);

  [[nodiscard]] value_type cast() const {
    return value_;
  }
};

static constexpr entity_id_t null_entity_id{std::numeric_limits<entity_id_t::value_type>::max()};

struct index_t : type_safe::strong_typedef<index_t, std::uint32_t>,
                 type_safe::strong_typedef_op::equality_comparison<index_t> {
  using strong_typedef::strong_typedef;
  using value_type = decltype(value_);

  [[nodiscard]] value_type cast() const {
    return value_;
  }
};

static constexpr index_t null_index{std::numeric_limits<entity_id_t::value_type>::max()};

inline std::ostream& operator<<(std::ostream& out, const entity_id_t& entity_id) {
  return out << entity_id.cast();
}

inline std::ostream& operator<<(std::ostream& out, const index_t& index) {
  return out << index.cast();
}

namespace std {

template <>
struct hash<entity_id_t> {
  std::size_t operator()(const entity_id_t& x) const noexcept {
    return std::hash<entity_id_t::value_type>()(x.cast());
  }
};

template <>
struct hash<index_t> {
  std::size_t operator()(const index_t& x) const noexcept {
    return std::hash<index_t::value_type>()(x.cast());
  }
};

} // namespace std
