#pragma once

#include <turn_based/ability.h>
#include <turn_based/board_helpers.h>
#include <turn_based/game_controller.h>
#include <turn_based/states.h>

/**
 * @brief Ability that can be used for caster neighboring fields.
 */
template <target_types TargetType = target_types::enemy, bool Available = false>
class neighboring_target_ability : public active_ability {
 public:
  neighboring_target_ability() = default;

  explicit neighboring_target_ability(
      std::string name, target_types target_type = TargetType, bool available = Available)
      : active_ability(std::move(name)), target_type_(target_type), available_(available) {}

  void prepare(index_t for_index) override {
    board_helpers::neighboring_fields(for_index, game_control().possible_movements, available_);
    game_control().current_targeting_type = target_type_;
    game_control().wait_for_action([this](index_t index) { return use(index); });
  }

  virtual void use(index_t use_on_index) = 0;

 protected:
  const target_types target_type_{TargetType};
  const bool available_{Available};
};
