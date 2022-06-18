#pragma once

#include <turn_based/ai/behavior_node.h>

namespace ai {
namespace nodes {

DEFINE_BEHAVIOR_NODE(go_to)

DEFINE_BEHAVIOR_NODE(go_close_to_destination)

DEFINE_BEHAVIOR_NODE(go_close_to_target_index)

DEFINE_BEHAVIOR_NODE(can_go_to)

class run_around : public behavior_node {
 public:
  run_around();
  bool operator()(ai_knowledge& knowledge) override;

 private:
  std::vector<std::pair<std::int32_t, std::int32_t>> shifts;
  std::size_t shift_index;
};

}  // namespace nodes
}  // namespace ai
