#pragma once

#include <turn_based/caster_target_ability.h>
#include <turn_based/turn_system.h>

class invisibility final : public caster_target_ability {
 public:
  explicit invisibility(entity_id_t entity_id);

  [[nodiscard]] bool usable() const override {
    return !used_;
  }

 private:
  void use(index_t on_index) override;
  void hide_me();
  void show_me();

  static constexpr auto name = "invisibility";
  bool used_{false};
  const entity_id_t entity_id_;
  index_t index_{0};
  std::int32_t turn_counter_{0};
  const std::int32_t duration_{2};
  turn_scoped_connection invisibility_callback_;
};
