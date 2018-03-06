#include <core/board.h>
#include <components/applied_effects.h>
#include <sender.h>
#include <common/animations.h>
#include <managers/players_manager.h>
#include <common/make_message.h>
#include "missile_of_doom.h"
#include "damage_dealers.h"

missile_of_doom::missile_of_doom(std::uint32_t entity_id) {
	after_player_turn(entity_id, [this, entity_id]() {
		if (!used && accumulated_damage == 0) {
			accumulated_damage += damage;
		}
		used = false;
	});
}

std::string missile_of_doom::hint() const {
	std::string desc;
	desc = "accumulated_damage : " + std::to_string(accumulated_damage) + ".";
	return desc;
}

void missile_of_doom::use(std::uint32_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto caster_id = board::at(used_from_index);
	auto enemy_id = board::at(index_on);

	sender::send(make_animation_message("power_bullet", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(ranged_damage(damage + accumulated_damage, enemy_id, caster_id));

	accumulated_damage = 0;

	used = true;
}