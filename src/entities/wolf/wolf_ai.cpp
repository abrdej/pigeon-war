#include <boost/dll/alias.hpp>

#include <turn_based/ai/action_makers.h>
#include <turn_based/ai/movers.h>
#include <turn_based/ai/nodes_compositions.h>
#include <turn_based/ai/target_finders.h>
#include <turn_based/ai_factory_interface.h>

struct wolf_ai_factory : public ai_factory_interface {
  ai::behavior_node_ptr create() override;
};

ai::behavior_node_ptr wolf_ai_factory::create() {
  return ai::construct::make_sequence(std::make_shared<ai::nodes::find_lowest_health_target>(),
                                      std::make_shared<ai::nodes::go_close_to_target_index>(),
                                      std::make_shared<ai::nodes::attack_enemy>());
}

ai_factory_interface_ptr create_wolf_ai_factory() {
  return std::make_shared<wolf_ai_factory>();
}

BOOST_DLL_ALIAS(create_wolf_ai_factory, wolf_ai)
