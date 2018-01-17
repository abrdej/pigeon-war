#include <managers/entity_manager.h>
#include "change_rocket_type.h"
#include "rocket_launcher.h"

change_rocket_type::change_rocket_type(std::uint32_t entity_id)
		: entity_id(entity_id) { }

void change_rocket_type::use(std::uint32_t index_on) {

	if (used)
		return;

	auto entity = entity_manager::get(entity_id);
	auto rocket_launcher_ptr = std::static_pointer_cast<rocket_launcher>(entity.get<abilities>()->type(abilities::ability_types::offensive));

	if (rocket_launcher_ptr->was_used()) {
		return;
	}

	rocket_launcher_ptr->change_rocket_type();

	used = true;
}