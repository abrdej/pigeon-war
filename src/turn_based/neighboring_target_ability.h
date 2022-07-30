#pragma once

#include <turn_based/ability.h>
#include <turn_based/game_controller.h>
#include <turn_based/states.h>

template <target_types TargetType = target_types::enemy, bool Available = false>
class neighboring_target_ability : public active_ability {
 public:
  neighboring_target_ability() = default;
  explicit neighboring_target_ability(std::string name) : active_ability(std::move(name)) {}

  void prepare(index_t for_index) override {
    game_control().selected_index_ = for_index;
    board_helper::neighboring_fields(for_index, game_control().possible_movements_, available);

    game_control().actual_targeting_type_ = target_type;
    game_control().wait_for_action([this](index_t index) { return use(index); });
  }

  virtual void use(index_t use_on_index) = 0;

 protected:
  const target_types target_type{TargetType};
  const bool available{Available};
};
