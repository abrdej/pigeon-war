#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>
#include <effects/aura_of_armor_effect.h>
#include <effects/auras_observer.h>
#include <aura_of_immunity.h>
#include <turn_based/path_finder.h>
#include <turn_based/board.h>
#include <components/applied_effects.h>
#include <components/modification.h>
#include <turn_based/sender.h>
#include <turn_based/move.h>

aura_of_immunity::aura_of_immunity(std::uint32_t entity_id)
		: entity_id(entity_id) {

	game::get<entity_manager>().get(entity_id).get<modification>()->modify_by(modifiers::damage_receiver, -damage_reduction_for_owner);

	game::get<auras_observer>().add_aura(entity_id, std::make_shared<aura_of_armor_effect>(entity_id, damage_reduction_for_friends));

	//game::get<entity_manager>().on_destroy(entity_id, [entity_id]() {
	//	auras_observer::remove_aura(entity_id);
	//});
}