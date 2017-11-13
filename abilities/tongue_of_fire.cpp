#include "tongue_of_fire.h"

#include "core/path_finder.h"
#include "core/states.h"
#include "core/board.h"
#include "bullet.h"
#include "animation/animation.h"
#include "animation/animation_impl.h"
#include "damage_dealers.h"

tongue_of_fire::tongue_of_fire()
	: used_(false)
{
	onEveryTurn([this](){
		refresh_usable();
	});
}

void tongue_of_fire::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
		states::state_controller::possible_movements_costs_, range_);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void tongue_of_fire::use(size_t index_on)
{
	if (used_)
		return;

	used_ = true;
	auto used_from_index = states::state_controller::selected_index_;

	play_bullet_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(damage_, index_on);

	// show damage animation // for example. -9 dmg
}

void tongue_of_fire::play_bullet_animation(size_t from_index, size_t to_index)
{
	//animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index + 1, std::chrono::milliseconds(50), "shoot.png"));
	//animation::base_player::play();
	animation::player<animation::move>::launch(animation::move(from_index, to_index, typeid(*this)));
	animation::base_player::play();
}

void tongue_of_fire::refresh_usable()
{
	used_ = false;
}