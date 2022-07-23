#pragma once

#include <turn_based/ability.h>
#include <turn_based/per_turn_usable.h>

class sniper_shot final : public active_ability, per_turn_usable {
 public:
  explicit sniper_shot(id_t entity_id);

  bool usable() const override {
    return !used;
  }

  void prepare(std::uint32_t for_index) override;

  void use(std::uint32_t index_on);

 private:
  static constexpr auto name = "sniper_shot";
  id_t entity_id_;
  std::int32_t range_{10};
  std::int32_t damage_{12};
  std::int32_t additional_damage_{12};
};
