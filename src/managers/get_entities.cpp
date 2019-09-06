#include <managers/get_entities.h>

#include <components/power_field.h>

std::unordered_map<std::uint32_t,
                   std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>
get_entities() {
  std::unordered_map<std::uint32_t,
                     std::tuple<std::string, std::int32_t, std::int32_t, std::uint32_t>>
      returned_map;
  game::get<entity_manager>().for_all([&returned_map](base_entity entity) {
    returned_map.emplace(
        entity.entity_id,
        std::make_tuple(entity.name, entity.get<health_field>()->health,
                        entity.contain<power_filed>() ? entity.get<power_filed>()->power
                                                      : std::numeric_limits<std::int32_t>::max(),
                        game_board().index_for(entity.entity_id)));
  });
  return std::move(returned_map);
}
