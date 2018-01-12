#include "ball_and_chain.h"
#include "managers/abilities_manager.h"
#include "managers/additions_manager.h"
#include "core/board.h"
#include "moveable.h"
#include "damage_dealers.h"

ball_and_chain::ball_and_chain(sf::Uint64 entity_id) : entity_id(entity_id) {

}

void ball_and_chain::use(sf::Uint64 index_on) {

	if (used_)
		return;

	auto enemy_id = board::at(index_on);

	auto& enemy_abilities = abilities_manager::component_for(enemy_id);
	auto moveable_ptr =  std::static_pointer_cast<moveable>(enemy_abilities.type(abilities::ability_types::moving));

	moveable_ptr->set_cost_callback([dealer_id = entity_id, dmg = damage_per_cost, enemy_id](sf::Int32 cost) {
		damage_dealers::standard_damage_dealer(magic_damage(cost * dmg, enemy_id, dealer_id));
	});

	auto slow_down_receiver =
			turn::turn_system::every_turn([effect_duration = duration, enemy_id, counter = 0]() mutable {

				if (counter++ == effect_duration * 2) {

					auto& inner_enemy_abilities = abilities_manager::component_for(enemy_id);
					auto inner_moveable_ptr =  std::static_pointer_cast<moveable>(inner_enemy_abilities.type(abilities::ability_types::moving));

					inner_moveable_ptr->remove_cost_callback();

					additions_manager::remove_component(enemy_id,
														"ball_and_chain_effect");
				}
			});

	additions_manager::add_component(enemy_id, "ball_and_chain_effect", slow_down_receiver);

	used_= true;
}
