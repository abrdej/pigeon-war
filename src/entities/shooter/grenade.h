#pragma once

#include <turn_based/configurable.h>
#include <turn_based/hint_configuration.h>
#include <turn_based/path_target_ability.h>

class grenade final : public path_target_ability, private configurable, private hint_configuration {
 public:
  explicit grenade(id_t entity_id);

  // TODO: replace this with something, I think it could be ability name that must be passed to ability.
  ADD_BITMAP_GETTER(grenade)

  [[nodiscard]] bool usable() const override;

 private:
  void use(index_t on_index) override;

  const id_t entity_id_;
  std::int32_t damage_{12};
  bool used_{false};
};
