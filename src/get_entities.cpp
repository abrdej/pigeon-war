#include <get_entities.h>

#include <turn_based/board.h>
#include <turn_based/components/health_field.h>
#include <turn_based/components/power_field.h>
#include <turn_based/managers/entity_manager.h>

entities_map get_entities() {
  entities_map entities;
  game::get<entity_manager>().for_all([&entities](base_entity entity) {
    entities.emplace(entity.entity_id,
                     std::make_tuple(entity.name,
                                     entity.get<health_field>()->health,
                                     entity.contain<power_filed>() ? entity.get<power_filed>()->power
                                                                   : std::numeric_limits<std::int32_t>::max(),
                                     game_board().index_for(entity.entity_id)));
  });
  return entities;
}
