#pragma once

#include <turn_based/path_target_ability.h>

class hypnosis final : public path_target_ability {
 public:
  explicit hypnosis(entity_id_t entity_id);

  bool usable() const override {
    return !used_;
  }

 private:
  void use(index_t index_on);

  static constexpr auto name = "hypnosis";
  bool used_{false};
  static constexpr auto range = 4;
  const std::int32_t duration_{1};
};
