#include <core/states_controller.h>
#include "bludgeon.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

void bludgeon::use(std::uint32_t index_on)
{
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto enemy_id = board::at(index_on);

	auto from_pos = board::to_pos(used_from_index);
	auto on_pos = board::to_pos(index_on);

	std::int32_t x_diff = from_pos.first - on_pos.first;
	std::int32_t y_diff = from_pos.second - on_pos.second;

	std::int32_t push_x = on_pos.first - x_diff;
	std::int32_t push_y = on_pos.second - y_diff;

	auto push_to_index = board::to_index(push_x, push_y);
	auto set_on_index = index_on;

	if (board::empty(push_to_index)) {

		board::move(index_on, push_to_index);
		board::move(used_from_index, index_on);

		sender::send(message_types::animation,
					 animation_def::bludgeon_push,
					 used_from_index,
					 index_on,
					 push_to_index);

		damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

		states::state_controller::possible_movements_.clear();
		states::state_controller::selected_index_ = set_on_index;

	} else {
		sender::send(message_types::animation,
					 animation_def::bludgeon,
					 used_from_index,
					 index_on);

		damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, entity_id));

		states::state_controller::possible_movements_.clear();
	}
}