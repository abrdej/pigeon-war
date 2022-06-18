#include <boost/dll/alias.hpp>

#include <turn_based/ai/action_makers.h>
#include <turn_based/ai/nodes_compositions.h>
#include <turn_based/ai/target_finders.h>
#include <turn_based/ai_factory_interface.h>

struct saurian_ai_factory : public ai_factory_interface {
  ai::behavior_node_ptr create() override;
};

ai::behavior_node_ptr saurian_ai_factory::create() {
  auto lowest_health_target_sequence =
      ai::construct::make_sequence(std::make_shared<ai::nodes::find_lowest_health_target>(),
                                   std::make_shared<ai::nodes::attack_enemy>());

  auto nearest_target_sequence =
      ai::construct::make_sequence(std::make_shared<ai::nodes::find_nearest_enemy>(),
                                   std::make_shared<ai::nodes::attack_enemy>());

  return ai::construct::make_selector(lowest_health_target_sequence, nearest_target_sequence);
}

ai_factory_interface_ptr create_saurian_ai_factory() {
  return std::make_shared<saurian_ai_factory>();
}

BOOST_DLL_ALIAS(create_saurian_ai_factory, saurian_ai)
