#include <get_button_description.h>

#include <turn_based/abilities.h>
#include <turn_based/board.h>
#include <turn_based/managers/entity_manager.h>

std::string get_button_description(index_t selected_index, std::uint32_t button_id) {
  auto entity_id = game_board().at(selected_index);
  auto entity = game::get<entity_manager>().get(entity_id);

  std::string description;
  if (entity.contain<abilities>()) {
    auto abilities_ptr = entity.get<abilities>();
    if (abilities_ptr && abilities_ptr->is_active) {
      auto entity_ability = abilities_ptr->at(button_id);
      if (entity_ability) {
        description = entity_ability->hint();
      }
    }
  }

  return std::move(description);
}
