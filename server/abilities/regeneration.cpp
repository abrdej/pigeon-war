#include "regeneration.h"
#include "managers/entity_manager.h"
#include "components/damage_taker.h"
#include "damage_dealers.h"

regeneration::regeneration(std::uint32_t entity_id) : entity_id(entity_id) {

	on_every_two_turns_from_next([this]() {

		auto entity = entity_manager::get(this->entity_id);
		auto health_field_ptr = entity.get<health_field>();

		auto missing_health = health_field_ptr->base_health - health_field_ptr->health;

		auto regeneration_increase_factor = missing_health / 5;

		auto regeneration = regeneration_increase_factor * regeneration_per_factor;

		if (regeneration > 0) {

			damage_dealers::standard_healing(healing(regeneration, this->entity_id));
		}
	});
}

std::string regeneration::hint() const {
	return "";
}