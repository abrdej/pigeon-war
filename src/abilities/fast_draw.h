#pragma once

#include <abilities/ability.h>
#include <abilities/per_turn_usable.h>

class fast_draw final : public passive_ability
{
public:
  explicit fast_draw(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(fast_draw)

  DEFINE_DESC_ONE(fast_draw, damage)

private:
  void use(std::uint32_t index_on);

  const std::uint32_t entity_id;
  const std::int32_t damage{8};
  const std::int32_t range{4};
};
