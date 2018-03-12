#include <common/make_message.h>
#include "dodge.h"
#include "sender.h"
#include "components/damage_taker.h"

dodge::dodge(std::uint32_t entity_id) {

	set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

		if (++counter == 3) {

			counter = 0;

			auto index = board::index_for(entity_id);

			sender::send(make_action_message("dodge", index));

			return 0;

		} else {
			auto final_damage = std::min(health_pack.health, dmg.damage_value);
			health_pack.health -= final_damage;

			return final_damage;
		}
	});
}