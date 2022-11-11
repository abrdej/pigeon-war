#include <get_entity_description.h>

#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>

std::string get_entity_description(index_t selected_index) {
  auto entity_id = game_board().at(selected_index);
  auto entity = game::get<entity_manager>().get(entity_id);
  return entity.description;
}
