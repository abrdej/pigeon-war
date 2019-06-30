#pragma once

#include <abilities/ability.h>
#include <abilities/per_turn_usable.h>
#include <abilities/path_target_ability.h>

class revolver final : public path_target_ability<4>,
                       turn_callback_helper
{
public:
  explicit revolver(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(revolver)

  DEFINE_DESC_ONE(revolver, damage)

private:
  void use(std::uint32_t index_on) final;

  const std::uint32_t entity_id;
  const std::int32_t damage{7};
  const std::int32_t additional_damage{2};
  const std::int32_t range{4};
  bool additional_shot{false};
  bool used{false};
};
