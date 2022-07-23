#pragma once

#include <turn_based/configurable.h>
#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class drain final : public neighboring_target_ability<>, per_turn_usable, configurable {
 public:
  explicit drain(std::uint32_t entity_id);

  bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on) override;

  static constexpr auto name = "drain";
  const std::uint32_t entity_id_;
  const std::int32_t damage_ = 10;
  const std::int32_t drain_amount_ = 4;
};
