#pragma once

#include <vector>

#include <turn_based/ability.h>
#include <turn_based/per_turn_usable.h>

class sabers final : public active_ability, per_turn_usable {
 public:
  explicit sabers(entity_id_t entity_id);

  [[nodiscard]] bool usable() const override {
    return !used;
  }

 private:
  void prepare(std::uint32_t for_index) override;
  void target(std::uint32_t on);
  void use(std::uint32_t index_on);

  static constexpr auto name = "sabers";
  const entity_id_t entity_id_;
  const std::int32_t damage_{7};
  std::vector<std::uint32_t> targets_;
};
