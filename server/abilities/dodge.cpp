#include "dodge.h"
#include "managers/health_manager.h"

dodge::dodge(std::size_t entity_id) {

	healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

		if (++counter == 3) {

			counter = 0;

			auto index = board::index_for(entity_id);

			sender::send(message_types::animation, animation_def::dodge, index);

			return 0;

		} else {
			auto final_damage = std::min(health_pack.health, dmg.damage_value);
			health_pack.health -= final_damage;

			return final_damage;
		}
	});
}

std::string dodge::hint() const {

	std::string desc;
	desc = "Dodge - samurai avoids every third attack.\n"
			"Received attacks from the last dodge: " + std::to_string(counter) + ".";
	return std::move(desc);
}
