#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class stamp final : public neighboring_target_ability<>,
                           per_turn_usable {
public:
  explicit stamp(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(stamp)

  DEFINE_DESC(stamp, damage_, stamps_, stun_duration_)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t on_index) override;

private:
  std::uint32_t entity_id_;
  std::int32_t damage_{6};
  std::int32_t stamps_{0};
  std::int32_t stamps_to_stun_{3};
  std::int32_t stun_duration_{1};
  std::int32_t sparks_duration_{2};
  std::uint32_t healing_amount_{5};
};
