#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class sword_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
  explicit sword_blow(std::uint32_t entity_id);

  [[nodiscard]] bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) override;

  static constexpr auto name = "sword_blow";
  std::uint32_t entity_id_;
  std::int32_t damage_{10};
};
