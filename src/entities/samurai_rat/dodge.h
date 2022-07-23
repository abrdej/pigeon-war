#pragma once

#include <turn_based/ability.h>

class dodge final : public passive_ability {
 public:
  explicit dodge(std::uint32_t entity_id);

 private:
  static constexpr auto name = "dodge";
  std::uint32_t entity_id_;
  int counter_{0};
};
