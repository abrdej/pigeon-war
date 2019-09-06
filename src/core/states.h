#pragma once

#include <cstdint>
#include <limits>

enum class states_types { waiting, wait_for_action };

static const std::uint32_t no_selected_index = std::numeric_limits<std::uint32_t>::max();

enum class target_types { caster, enemy, friendly, neutral, moving, all, non };

struct target_types_key_hash {
  template <typename T>
  std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};
