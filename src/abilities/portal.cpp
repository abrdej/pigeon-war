#include <sender.h>
#include <core/board.h>
#include <managers/players_manager.h>
#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <messages/make_message.h>
#include "portal.h"
#include "possible_move_helper.h"

portal::portal(std::uint32_t entity_id) : entity_id(entity_id) {

}

void portal::prepare(std::uint32_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::all_free(states::state_controller::possible_movements_);

	states::state_controller::actual_targeting_type_ = target_types::moving;
	states::state_controller::wait_for_action([this, for_index](std::uint32_t index)
											  {
												  return use(for_index, index);
											  });
}

void portal::use(std::uint32_t from_index, std::uint32_t to_index) {

	if (used)
		return;

	auto& power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

	if (power < power_cost)
		return;

	auto center_pos = game::get<board>().to_pos(from_index);
	auto destination_pos = game::get<board>().to_pos(to_index);

	std::vector<std::uint32_t> around_fields_ids;
	board_helper::neighboring_fields(from_index, around_fields_ids, false);

    std::vector<std::pair<std::uint32_t, std::uint32_t>> neighboring_moves;

	for (auto&& field_id : around_fields_ids) {
		if (!game::get<board>().empty(field_id) && !players_funcs::neutral_entity(field_id)) {

			auto pos = game::get<board>().to_pos(field_id);

			auto x_diff = center_pos.first - pos.first;
			auto y_diff = center_pos.second - pos.second;

			auto x_dest = destination_pos.first - x_diff;
			auto y_dest = destination_pos.second - y_diff;

			auto dest_index = game::get<board>().to_index(x_dest, y_dest);

			if (game::get<board>().empty(dest_index)) {
				game::get<board>().move(field_id, dest_index);
                neighboring_moves.emplace_back(field_id, dest_index);
			}
		}
	}

	game::get<board>().move(from_index, to_index);

	sender::send(make_action_message("portal", from_index, to_index, neighboring_moves));

	states::state_controller::selected_index_ = to_index;

	power -= power_cost;

	used = true;
}