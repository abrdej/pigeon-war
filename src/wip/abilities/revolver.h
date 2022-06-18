#pragma once

#include <turn_based/ability.h>
#include <turn_based/per_turn_usable.h>
#include <turn_based/path_target_ability.h>

class revolver final : public path_target_ability,
                       turn_callback_helper
{
public:
  explicit revolver(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(revolver)

  DEFINE_DESC_ONE(revolver, damage)

  bool usable() const override {
    return !used;
  }

private:
  void use(std::uint32_t index_on) final;

  const std::uint32_t entity_id;
  const std::int32_t damage{7};
  const std::int32_t additional_damage{2};
  const std::int32_t range{4};
  bool additional_shot{false};
  bool used{false};
};
