#pragma once

#include <turn_based/configurable.h>
#include <turn_based/hint_configuration.h>
#include <turn_based/per_turn_usable.h>
#include <turn_based/straight_target_ability.h>

class blow_the_ax final : public straight_target_ability<1>,
                          private per_turn_usable,
                          private configurable {
public:
  explicit blow_the_ax(std::uint32_t entity_id);

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t on_index) override;

  static constexpr auto name = "blow_the_ax";
  std::uint32_t entity_id_;
  std::int32_t damage_{15};
};
