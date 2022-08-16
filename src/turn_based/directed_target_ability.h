#pragma once

#include <turn_based/ability.h>
#include <turn_based/board_helpers.h>
#include <turn_based/game_controller.h>
#include <turn_based/states.h>

template <std::int32_t Range, target_types TargetType = target_types::enemy, bool SkipObstacles = false>
class directed_target_ability : public active_ability {
 public:
  directed_target_ability() = default;

  explicit directed_target_ability(std::string name) : active_ability(std::move(name)) {}

  void prepare(index_t index) override {
    game_control().selected_index_ = index;

    board_helpers::calc_directed(index,
                                 game_control().possible_movements_,
                                 game_control().possible_movements_costs_,
                                 range_,
                                 skip_obstacles_);

    game_control().actual_targeting_type_ = target_type_;
    game_control().wait_for_action([this](index_t used_on_index) {
      return use(used_on_index);
    });
  }

  virtual void use(index_t use_on_index) = 0;

 protected:
  std::int32_t range_{Range};
  const target_types target_type_{TargetType};
  const bool skip_obstacles_{SkipObstacles};
};
