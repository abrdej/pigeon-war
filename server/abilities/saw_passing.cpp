#include "saw_passing.h"

#include <core/states_controller.h>
#include <core/board.h>
#include <common/make_message.h>
#include "damage_dealers.h"
#include "sender.h"

saw_passing::saw_passing(std::uint32_t entity_id) : entity_id(entity_id) {

}

void saw_passing::use(std::uint32_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto from_pos = board::to_pos(index_on);
	auto to_pos = board::to_pos(used_from_index);

	std::int32_t xx = static_cast<std::int32_t>(from_pos.first) - static_cast<std::int32_t>(to_pos.first);
	std::int32_t yy = static_cast<std::int32_t>(from_pos.second) - static_cast<std::int32_t>(to_pos.second);

	auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

	sender::send(make_action_message("saw_passing", used_from_index, index_to_move));

	board::move(used_from_index, index_to_move);

	std::vector<std::uint32_t> indexes;

	if (xx != 0) {
		for (std::int32_t x = xx > 0 ? 1 : -1; std::abs(x) < std::abs(xx); x = xx > 0 ? x + 1 : x - 1) {

			auto index = board::to_index(to_pos.first + x, to_pos.second);

			if (!board::empty(index)) {
				damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(index), entity_id));

				if (std::abs(x) != std::abs(xx)) {
					indexes.push_back(index);
				}
			}
		}
	} else {
		for (std::int32_t y = yy > 0 ? 1 : -1; abs(y) < abs(yy); y = yy > 0 ? y + 1 : y - 1) {

			auto index = board::to_index(to_pos.first, to_pos.second + y);

			if (!board::empty(index)) {
				damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(index), entity_id));

				if (std::abs(y) != std::abs(yy)) {
					indexes.push_back(index);
				}
			}
		}
	}

	states::state_controller::selected_index_ = index_on;

	states::state_controller::possible_movements_.clear();
	states::state_controller::custom_valid_targets[entity_id].clear();

	used = true;
}

std::string saw_passing::hint() const {

	std::string desc;
	return std::move(desc);
}