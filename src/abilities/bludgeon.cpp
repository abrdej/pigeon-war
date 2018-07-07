#include <core/states_controller.h>
#include <messages/make_message.h>
#include "bludgeon.h"
#include "damage_dealers.h"
#include "sender.h"

bludgeon::bludgeon(std::uint32_t entity_id) {
	after_player_turn(entity_id, [this]() {
		if (!used) {
			rage_damage = std::max(0, rage_damage - 1);
		}
		used = false;
	});
}

void bludgeon::use(std::uint32_t index_on)
{
	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = game::get<board>().at(used_from_index);

	auto enemy_id = game::get<board>().at(index_on);

	auto from_pos = game::get<board>().to_pos(used_from_index);
	auto on_pos = game::get<board>().to_pos(index_on);

	std::int32_t x_diff = from_pos.first - on_pos.first;
	std::int32_t y_diff = from_pos.second - on_pos.second;

	std::int32_t push_x = on_pos.first;
	std::int32_t push_y = on_pos.second;

	while (true) {
		auto dx = push_x - x_diff;
		auto dy = push_y - y_diff;

		auto index = game::get<board>().to_index(dx, dy);

		if (!game::get<board>().empty(index))
			break;

		push_x = dx;
		push_y = dy;
	}

	auto push_to_index = game::get<board>().to_index(push_x, push_y);
	auto set_on_index = index_on;

	if (game::get<board>().empty(push_to_index)) {

		game::get<board>().move(index_on, push_to_index);
		game::get<board>().move(used_from_index, index_on);

		sender::send(make_action_message("bludgeon_push", used_from_index, index_on, push_to_index));

		damage_dealers::standard_damage_dealer(melee_damage(damage + rage_damage, enemy_id, entity_id));

		states::state_controller::possible_movements_.clear();
		states::state_controller::selected_index_ = set_on_index;

	} else {
		sender::send(make_action_message("bludgeon", used_from_index, index_on));

		damage_dealers::standard_damage_dealer(melee_damage(damage + rage_damage, enemy_id, entity_id));

		states::state_controller::possible_movements_.clear();
	}

	rage_damage += 1;

	std::cout << "Rage damage :" << rage_damage << "\n";

	used = true;
}