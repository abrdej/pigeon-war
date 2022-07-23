#pragma once

#include <turn_based/defs.h>
#include <turn_based/per_turn_usable.h>
#include <turn_based/straight_target_ability.h>

class shoot final : public directed_target_ability<3>, private per_turn_callback {
 public:
  explicit shoot(id_t entity_id);

  [[nodiscard]] bool usable() const override;

 private:
  void use(index_t on_index) override;

  static constexpr auto name = "shoot";
  const id_t entity_id_;
  const std::int32_t bullets_per_turn_{2};
  const std::int32_t damage_{6};
  std::int32_t bullets_{bullets_per_turn_};
};
