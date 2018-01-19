#include <managers/entity_manager.h>
#include <managers/players_manager.h>
#include <effects/aura_of_immunity_effect.h>
#include <effects/auras_observer.h>
#include "aura_of_immunity.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "components/additions.h"
#include "components/modification.h"
#include "sender.h"
#include "common/animations.h"
#include "moveable.h"

aura_of_immunity::aura_of_immunity(std::uint32_t entity_id)
		: entity_id(entity_id) {

	entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction_for_owner);

	auras_observer::add_aura(entity_id, std::make_shared<aura_of_immunity_effect>(damage_reduction_for_friends));
}

std::string aura_of_immunity::hint() const {

	std::string desc;
	desc = "Aura Of Immunity - giant offers a nearby allies aure\n"
				   "which apply damage reduction of " + std::to_string(damage_reduction_for_friends) + ".\n"
			"Giant also has constant damage reduction by " + std::to_string(damage_reduction_for_owner) + ".";

	return std::move(desc);
}