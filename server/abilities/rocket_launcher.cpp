#include <sender.h>
#include <common/animations.h>
#include <common/make_message.h>
#include <managers/entity_manager.h>
#include "rocket_launcher.h"
#include "damage_dealers.h"
#include "core/board.h"
#include "abilities.h"
#include "mortar_thrower.h"

void rocket_launcher::use(std::uint32_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto mortal_thrower_ptr = entity_manager::get(entity_id).get<abilities>()->get<mortar_thrower>();
	if (mortal_thrower_ptr->was_used())
		return;

	bool has_bonus = *entity_manager::get(entity_id).get<rocket_types>() != rocket_types::long_range_rocket;
    *entity_manager::get(entity_id).get<rocket_types>() = rocket_types::long_range_rocket;

    std::cout << "has_bonus: " << has_bonus << "\n";

	auto enemy_id = board::at(index_on);

	auto used_from_pos = board::to_pos(used_from_index);
	auto used_to_pos = board::to_pos(index_on);

	auto distance = std::max(std::abs(static_cast<std::int32_t>(used_from_pos.first) - static_cast<std::int32_t>(used_to_pos.first)),
							 std::abs(static_cast<std::int32_t>(used_from_pos.second) - static_cast<std::int32_t>(used_to_pos.second)));

	auto final_damage = static_cast<std::int32_t>(base_damage + distance * distance_bonus + (has_bonus ? rocket_change_bonus : 0));

	sender::send(make_action_message("rocket_launcher", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(ranged_damage(final_damage, enemy_id, entity_id));

	used = true;

}