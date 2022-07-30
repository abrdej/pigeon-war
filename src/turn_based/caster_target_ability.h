#pragma once

#include <turn_based/ability.h>
#include <turn_based/game_controller.h>
#include <turn_based/states.h>

struct caster_target_ability : active_ability {
  caster_target_ability() = default;
  explicit caster_target_ability(std::string name) : active_ability(std::move(name)) {}
  void prepare(index_t for_index) override {
    game_control().actual_state_ = states_types::wait_for_action;
    game_control().possible_movements_.clear();
    game_control().possible_movements_.push_back(for_index);
    game_control().actual_targeting_type_ = target_types::caster;
    game_control().wait_for_action([this](index_t index) {
      return use(index);
    });
  }
  virtual void use(index_t use_on_index) = 0;
};
