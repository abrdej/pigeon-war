#include "barrier.h"
#include <managers/entity_manager.h>
#include "immortality.h"
#include "components/damage_taker.h"
#include "sender.h"
#include "common/animations.h"

barrier::barrier(std::uint32_t entity_id) : entity_id(entity_id) {

	set_damage_receiver(entity_id, [this](health_field& health_pack, const damage_pack& dmg) mutable {

		auto damage = dmg.damage_value;

		if (is_barrier_active) {
			auto damage_for_barrier = std::min(barrier_strength, damage);
			barrier_strength -= damage_for_barrier;

			damage = dmg.damage_value - damage_for_barrier;

			play_change_health_animation(board::index_for(this->entity_id), damage_for_barrier);
		}

		auto final_damage = std::min(health_pack.health, damage);
		health_pack.health -= final_damage;

		auto missing_health = health_pack.base_health - health_pack.health;

		if (missing_health > 35 && !is_barrier_active && !was_barrier_active) {
			is_barrier_active = true;
			was_barrier_active = true;

			barrier_holder = make_after_n_round_callback_holder(duration, [this]() {
				is_barrier_active = false;
			});
		}

		return final_damage;
	});
}

std::string barrier::hint() const {

	std::string desc;
	desc = "Immortality - when the health of the warrior drops to zero\n"
			"the warrior becomes immortal for one more turn.";

	return std::move(desc);

}