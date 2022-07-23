#pragma once

#include <turn_based/configurable.h>
#include <turn_based/path_target_ability.h>

class grenade final : public path_target_ability, private configurable {
 public:
  explicit grenade(id_t entity_id);

  [[nodiscard]] bool usable() const override;

 private:
  void use(index_t on_index) override;

  static constexpr auto name = "grenade";
  const id_t entity_id_;
  std::int32_t damage_{12};
  bool used_{false};
};
