#include "basic_melee_attack.h"

#include "core/path_finder.h"
#include "core/states.h"
#include "core/board.h"
#include "bullet.h"
#include "animation/animation.h"
#include "animation/animation_impl.h"
#include "damage_dealers.h"
#include "managers/types_manager.h"

basic_melee_attack::basic_melee_attack()
{
	onEveryRound([this]() {
		used = false;
	});
}

void basic_melee_attack::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;
	board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void basic_melee_attack::use(size_t index_on)
{
	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto caster_id = board::at(index_on);

	play_animation(used_from_index, index_on);

	auto enemy_id = board::at(index_on);

	damage_dealers::standard_damage_dealer(melee_damage(damage_, enemy_id, caster_id));

	used = true;

	// show damage animation // for example. -9 dmg
	//states::state_controller::target_fields(states::target_types::non);
}

void basic_melee_attack::play_animation(size_t index_from, size_t index_on)
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
}