#pragma once

#include <turn_based/ability.h>
#include <turn_based/defs.h>

class dodge final : public passive_ability {
 public:
  explicit dodge(entity_id_t entity_id);

 private:
  static constexpr auto name = "dodge";
  const std::uint32_t entity_id_;
  int counter_{0};
};
