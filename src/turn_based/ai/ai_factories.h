#include <turn_based/ai/behavior_node.h>

#include <turn_based/ai/action_makers.h>
#include <turn_based/ai/movers.h>
#include <turn_based/ai/nodes_compositions.h>
#include <turn_based/ai/target_finders.h>

class saurian;
class wolf;
class golem;
class spectre;
class pixie;

namespace ai {

template <typename Entity>
behavior_node_ptr make_ai();

template <>
inline behavior_node_ptr make_ai<wolf>() {
  return ai::construct::make_sequence(std::make_shared<ai::nodes::find_lowest_health_target>(),
                                      std::make_shared<ai::nodes::go_close_to_target_index>(),
                                      std::make_shared<ai::nodes::attack_enemy>());
}

template <>
inline behavior_node_ptr make_ai<saurian>() {
  auto lowest_health_target_sequence =
      ai::construct::make_sequence(std::make_shared<ai::nodes::find_lowest_health_target>(),
                                   std::make_shared<ai::nodes::attack_enemy>());

  auto nearest_target_sequence =
      ai::construct::make_sequence(std::make_shared<ai::nodes::find_nearest_enemy>(),
                                   std::make_shared<ai::nodes::attack_enemy>());

  return ai::construct::make_selector(lowest_health_target_sequence, nearest_target_sequence);
}

template <>
inline behavior_node_ptr make_ai<golem>() {
  auto best_target_sequence = ai::construct::make_sequence(
      std::make_shared<ai::nodes::find_best_target_for_golem>(),
      std::make_shared<ai::nodes::find_position_for_shot>(),
      std::make_shared<ai::nodes::can_go_to>(), std::make_shared<ai::nodes::go_to>(),
      std::make_shared<ai::nodes::attack_enemy>());

  auto nearest_target_sequence = ai::construct::make_sequence(
      std::make_shared<ai::nodes::find_nearest_enemy>(),
      std::make_shared<ai::nodes::find_position_for_shot>(), std::make_shared<ai::nodes::go_to>(),
      std::make_shared<ai::nodes::attack_enemy>());

  return ai::construct::make_selector(best_target_sequence, nearest_target_sequence);
}

template <>
inline behavior_node_ptr make_ai<spectre>() {
  return ai::construct::make_sequence(std::make_shared<ai::nodes::find_nearest_enemy>(),
                                      std::make_shared<ai::nodes::go_close_to_target_index>(),
                                      std::make_shared<ai::nodes::attack_enemy>());
}

template <>
inline behavior_node_ptr make_ai<pixie>() {
  return ai::construct::make_selector(std::make_shared<ai::nodes::run_around>(),
                                      std::make_shared<ai::nodes::attack_enemy>());
}

}  // namespace ai