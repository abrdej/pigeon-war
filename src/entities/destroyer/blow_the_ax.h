#pragma once

#include <turn_based/per_turn_usable.h>
#include <turn_based/straight_target_ability.h>

class blow_the_ax final : public straight_target_ability<1>,
                          private per_turn_usable {
public:
  explicit blow_the_ax(entity_id_t entity_id);

  bool usable() const override {
    return !used;
  }

private:
  void use(index_t on_index) override;

  static constexpr auto name = "blow_the_ax";
  const entity_id_t entity_id_;
  std::int32_t damage_{15};
};
