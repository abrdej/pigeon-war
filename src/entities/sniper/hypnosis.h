#pragma once

#include <turn_based/path_target_ability.h>

class hypnosis final : public path_target_ability {
 public:
  hypnosis();

  bitmap_key get_bitmap_key() const override {
    return "hypnosis";
  }

  DEFINE_DESC_ZERO(hypnosis)

  bool usable() const override {
    return !used;
  }

 private:
  void use(std::uint32_t index_on);

  bool used{false};
  const std::int32_t range{4};
  const std::int32_t duration{1};
};
