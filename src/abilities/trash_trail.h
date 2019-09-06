#pragma once

#include <abilities/ability.h>
#include <components/damage_taker.h>
#include <core/turn_system.h>

class trash_trail final : public passive_ability, protected turn_callback_helper {
public:
  explicit trash_trail(std::uint32_t entity_id);
  ~trash_trail();

  ADD_BITMAP_GETTER(trash_trail)

private:
  const std::uint32_t entity_id_;
  const std::int32_t activation_health_amount_{25};
  damage_connection connection_;
};
