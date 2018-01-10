#include "laser.h"
#include "damage_dealers.h"
#include <core/states_controller.h>

void laser::use(size_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	auto from_pos = board::to_pos(index_on);
	auto to_pos = board::to_pos(used_from_index);

	int hor_diff = static_cast<int>(from_pos.first) - static_cast<int>(to_pos.first);
	int ver_diff = static_cast<int>(from_pos.second) - static_cast<int>(to_pos.second);

	int xx = 0;
	int yy = 0;

	if (hor_diff != 0) {
		xx = (hor_diff > 0 ? 1 : -1) * range;
	} else {
		yy = (ver_diff > 0 ? 1 : -1) * range;
	}

	auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

	sender::send(message_types::animation, animation_def::laser, used_from_index, index_to_move);

	if (hor_diff != 0) {
		for (int x = hor_diff > 0 ? 1 : -1; std::abs(x) <= std::abs(range); x = hor_diff > 0 ? x + 1 : x - 1) {

			auto index = board::to_index(to_pos.first + x, to_pos.second);

			if (!board::empty(index)) {
				auto enemy_id = board::at(index);
				damage_dealers::standard_damage_dealer(special_damage(damage, enemy_id, entity_id));

				auto dmg_receiver = healths_manager::get_damage_receiver(enemy_id);

				healths_manager::set_damage_receiver(enemy_id,
													 [dmg_receiver, bonus_dmg = bonus_damage](health_field& health_pack, const damage_pack& dmg) mutable {

														 auto damage = dmg_receiver(health_pack, dmg);

														 if (damage > 0) {
															 auto final_bonus_damage = std::min(health_pack.health, bonus_dmg);

															 health_pack.health -= final_bonus_damage;

															 damage += final_bonus_damage;
														 }
														 return damage;
													 });
			}
		}
	} else {
		for (int y = ver_diff > 0 ? 1 : -1; abs(y) <= abs(range); y = ver_diff > 0 ? y + 1 : y - 1) {

			auto index = board::to_index(to_pos.first, to_pos.second + y);

			if (!board::empty(index)) {
				auto enemy_id = board::at(index);
				damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index), entity_id));

				auto dmg_receiver = healths_manager::get_damage_receiver(enemy_id);

				healths_manager::set_damage_receiver(enemy_id,
													 [dmg_receiver, bonus_dmg = bonus_damage](health_field& health_pack,
																		  const damage_pack& dmg) mutable {

														 auto damage = dmg_receiver(health_pack, dmg);

														 auto final_bonus_damage = std::min(health_pack.health,
																							bonus_dmg);

														 health_pack.health -= final_bonus_damage;

														 return damage + final_bonus_damage;
													 });
			}
		}
	}

	used = true;
}