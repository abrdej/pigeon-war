#pragma once

#include <turn_based/ability.h>

class teleport final : public active_ability {
public:
  teleport() = default;

  ADD_BITMAP_GETTER(teleport)

  DEFINE_DESC_ZERO(teleport)

  bool usable() const override {
    return !used;
  }

private:
  void prepare(std::uint32_t for_index) override;

  void use(std::uint32_t from_index, std::uint32_t to_index);

private:
  bool used{false};
};
