#include <abilities/rocket_launcher.h>

#include <abilities/abilities.h>
#include <abilities/damage_dealers.h>
#include <abilities/mortar_thrower.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <server/sender.h>

rocket_launcher::rocket_launcher(std::uint32_t entity_id) : entity_id(entity_id) {}

void rocket_launcher::use(std::uint32_t on_index) {

	if (used)
		return;

	auto used_from_index = game_control().selected_index_;

	auto mortal_thrower_ptr = game::get<entity_manager>().get(entity_id).get<abilities>()->get<mortar_thrower>();
	if (mortal_thrower_ptr->was_used())
		return;

	bool has_bonus = *game::get<entity_manager>().get(entity_id).get<rocket_types>() != rocket_types::long_range_rocket;
    *game::get<entity_manager>().get(entity_id).get<rocket_types>() = rocket_types::long_range_rocket;

	auto used_from_pos = game_board().to_pos(used_from_index);
	auto used_to_pos = game_board().to_pos(on_index);

	auto distance = std::max(std::abs(static_cast<std::int32_t>(used_from_pos.first)
									  - static_cast<std::int32_t>(used_to_pos.first)),
							 std::abs(static_cast<std::int32_t>(used_from_pos.second)
									  - static_cast<std::int32_t>(used_to_pos.second)));

	auto final_damage = static_cast<std::int32_t>(base_damage + distance * distance_bonus
			+ (has_bonus ? rocket_change_bonus : 0));

	sender::send(make_action_message("rocket_launcher", used_from_index, on_index));

	damage_dealers::standard_damage_dealer(ranged_damage(final_damage, game_board().at(on_index), entity_id));

	used = true;
}
