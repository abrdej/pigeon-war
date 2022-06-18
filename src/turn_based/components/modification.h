#pragma once

#include <cstdint>
#include <unordered_map>

enum class modifiers { damage_receiver, damage_dealer, shot_range, move_range };

struct modifiers_key_hash {
  template <typename T>
  std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

class modification {
  std::unordered_map<modifiers, std::int32_t, modifiers_key_hash> modifiers_;

 public:
  void modify_by(modifiers modifier, std::int32_t value) { modifiers_[modifier] += value; }
  std::int32_t value(modifiers modifier) { return modifiers_[modifier]; }
};
