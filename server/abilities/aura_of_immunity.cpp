#include <managers/entity_manager.h>
#include <managers/players_manager.h>
#include <effects/aura_of_immunity_effect.h>
#include <effects/auras_observer.h>
#include "aura_of_immunity.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "components/applied_effects.h"
#include "components/modification.h"
#include "sender.h"
#include "common/animations.h"
#include "moveable.h"

aura_of_immunity::aura_of_immunity(std::uint32_t entity_id)
		: entity_id(entity_id) {

	entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction_for_owner);

	auras_observer::add_aura(entity_id, std::make_shared<aura_of_immunity_effect>(entity_id, damage_reduction_for_friends));

	//entity_manager::on_destroy(entity_id, [entity_id]() {
	//	auras_observer::remove_aura(entity_id);
	//});
}