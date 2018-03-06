#include "laser.h"
#include "damage_dealers.h"
#include <core/states_controller.h>
#include <common/make_message.h>
#include "sender.h"
#include "common/animations.h"
#include "components/damage_taker.h"

void laser::use(std::uint32_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto from_pos = board::to_pos(index_on);
	auto to_pos = board::to_pos(used_from_index);

	std::int32_t hor_diff = static_cast<std::int32_t>(from_pos.first) - static_cast<std::int32_t>(to_pos.first);
	std::int32_t ver_diff = static_cast<std::int32_t>(from_pos.second) - static_cast<std::int32_t>(to_pos.second);

	std::int32_t xx = 0;
	std::int32_t yy = 0;

	if (hor_diff != 0) {
		xx = (hor_diff > 0 ? 1 : -1) * range;
	} else {
		yy = (ver_diff > 0 ? 1 : -1) * range;
	}

	auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

	sender::send(make_animation_message("laser", used_from_index, index_to_move));

	if (hor_diff != 0) {
		for (std::int32_t x = hor_diff > 0 ? 1 : -1; std::abs(x) <= std::abs(range); x = hor_diff > 0 ? x + 1 : x - 1) {

			auto index = board::to_index(to_pos.first + x, to_pos.second);

			if (!board::empty(index)) {
				auto enemy_id = board::at(index);
				damage_dealers::standard_damage_dealer(special_damage(damage, enemy_id, entity_id));

				if (entity_manager::get(enemy_id).contain<modification>()) {
					entity_manager::get(enemy_id).get<modification>()->modify_damage_receiver_modifier_by(bonus_damage);
				}
			}
		}
	} else {
		for (std::int32_t y = ver_diff > 0 ? 1 : -1; abs(y) <= abs(range); y = ver_diff > 0 ? y + 1 : y - 1) {

			auto index = board::to_index(to_pos.first, to_pos.second + y);

			if (!board::empty(index)) {
				auto enemy_id = board::at(index);
				damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

				if (entity_manager::get(enemy_id).contain<modification>()) {
					entity_manager::get(enemy_id).get<modification>()->modify_damage_receiver_modifier_by(bonus_damage);
				}
			}
		}
	}

	used = true;
}

std::string laser::hint() const {

	std::string desc;
	desc = "Laser - deals damage of " + std::to_string(damage) + " to all targets in line.\n"
			"In addition, each hit target will now receive additional 1 point of damage\n"
																		 " from all units.\n"
			"This effect stacks.";

	return std::move(desc);
}