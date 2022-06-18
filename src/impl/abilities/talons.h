#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>
#include <turn_based/entity.h>

class talons final : public neighboring_target_ability<>, per_turn_usable {
public:
  explicit talons(std::uint32_t entity_id);

  ADD_BITMAP_GETTER(talons)

  DEFINE_DESC_ONE(talons, damage_)

  bool usable() const override {
    return !used;
  }

  void set_trash_trail_enemy_id(std::uint32_t enemy_id) {
    trash_trail_enemy_id_ = enemy_id;
  }

private:
  void use(std::uint32_t index_on) override;

private:
  const std::uint32_t entity_id_;
  const std::int32_t damage_{8};
  const std::int32_t damage_boost_for_trash_trail_{12};
  std::uint32_t trash_trail_enemy_id_{none_entity_id};
};
