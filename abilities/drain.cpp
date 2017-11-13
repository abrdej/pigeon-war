#include "drain.h"

#include "core/path_finder.h"
#include "core/states.h"
#include "core/board.h"
#include "bullet.h"
#include "animation/animation.h"
#include "animation/animation_impl.h"
#include "damage_dealers.h"
#include "managers/health_component.h"
#include "managers/types_manager.h"

drain::drain()
{
	onEveryTurn([this](){
		used = false;
	});
}

void drain::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void drain::use(size_t index_on)
{
	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;

	play_animation(used_from_index, index_on);
	
	auto dealt_damage = damage_dealers::standard_damage_dealer(damage_, index_on);

	auto entity_id = board::at(used_from_index);
	auto amount_of_health = std::min<int>(drain_, dealt_damage);
	healths_manager::receive_damage(entity_id, -amount_of_health);
	used = true;

	// show damage animation // for example. -9 dmg
	//states::state_controller::target_fields(states::target_types::non);
}

void drain::play_animation(size_t index_from, size_t index_on)
{
	auto entity_id = board::take(index_from);
	auto type = types_manager::component_for(entity_id);
	animation::player<animation::move>::launch(animation::move(index_from, index_on, type));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "claws.png"));
	animation::base_player::play();
	animation::player<animation::move>::launch(animation::move(index_on, index_from, type));
	animation::base_player::play();
	board::give_back(entity_id, index_from);
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index_from, std::chrono::milliseconds(150), "healthing.png"));
	animation::base_player::play();
}