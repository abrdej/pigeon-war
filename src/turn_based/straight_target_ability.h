#pragma once

#include <turn_based/ability.h>
#include <turn_based/board_helpers.h>
#include <turn_based/game_controller.h>
#include <turn_based/states.h>

template <std::int32_t Range = -1, target_types TargetType = target_types::enemy, bool SkipObstacles = false>
class straight_target_ability : public active_ability {
 public:
  straight_target_ability() = default;

  explicit straight_target_ability(std::string name) : active_ability(std::move(name)) {}

  explicit straight_target_ability(std::string name, std::int32_t range,
                                   target_types target_type = target_types::enemy, bool skip_obstacles = false)
      : active_ability(std::move(name)), range_(range), target_type_(target_type), skip_obstacles_(skip_obstacles) {}

  void prepare(index_t index) override {
    game_control().selected_index = index;

    board_helpers::calc_straight(index,
                                 game_control().possible_movements,
                                 game_control().possible_movements_costs,
                                 range_,
                                 skip_obstacles_);

    game_control().current_targeting_type = target_type_;
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
