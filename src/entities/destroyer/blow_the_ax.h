#pragma once

#include <turn_based/straight_target_ability.h>
#include <turn_based/per_turn_usable.h>

class blow_the_ax final : public straight_target_ability<1>,
                          per_turn_usable {
public:
  explicit blow_the_ax(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(blow_the_ax)

  DEFINE_DESC_ONE(blow_the_ax, damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t on_index) override;

  std::uint32_t entity_id;
  std::int32_t damage{15};
};
