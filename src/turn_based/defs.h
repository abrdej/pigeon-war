#pragma once

#include <cstdint>
#include <limits>
#include <ostream>

#include <type_safe/strong_typedef.hpp>

template <typename Tag>
struct tagged_uint : type_safe::strong_typedef<tagged_uint<Tag>, std::uint32_t>,
                     type_safe::strong_typedef_op::equality_comparison<tagged_uint<Tag>> {
  using type_safe::strong_typedef<tagged_uint<Tag>, std::uint32_t>::strong_typedef;
  using value_type = decltype(type_safe::strong_typedef<tagged_uint<Tag>, std::uint32_t>::value_);

  [[nodiscard]] value_type cast() const {
    return type_safe::strong_typedef<tagged_uint<Tag>, std::uint32_t>::value_;
  }
};

struct entity_id_tag {};
struct player_id_tag {};
struct index_tag {};

using entity_id_t = tagged_uint<entity_id_tag>;
static constexpr entity_id_t null_entity_id{std::numeric_limits<entity_id_t::value_type>::max()};

using player_id_t = tagged_uint<player_id_tag>;

using index_t = tagged_uint<index_tag>;
static constexpr index_t null_index{std::numeric_limits<entity_id_t::value_type>::max()};

template <typename T>
std::ostream& operator<<(std::ostream& out, const tagged_uint<T>& x) {
  return out << x.cast();
}

namespace std {

template <typename T>
struct hash<tagged_uint<T>> {
  std::size_t operator()(const tagged_uint<T>& x) const noexcept {
    return std::hash<typename tagged_uint<T>::value_type>()(x.cast());
  }
};

} // namespace std
