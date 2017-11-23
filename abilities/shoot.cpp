#include "shoot.h"

#include "core/path_finder.h"
#include "core/states.h"
#include "core/board.h"
#include "bullet.h"
#include "animation/animation.h"
#include "animation/animation_impl.h"
#include "damage_dealers.h"
#include "audio/audio_impl.h"

shoot::shoot()
	: bullets_(bullets_n)
{
	onEveryRound([this]() {
		refresh_usable();
	});
}

void shoot::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
		states::state_controller::possible_movements_costs_,
		range_);
	
	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void shoot::use(size_t index_on)
{
	if (bullets_ == 0)
		return;

	audio::shoot_sound();

	--bullets_;
	auto used_from_index = states::state_controller::selected_index_;

	play_bullet_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(damage_, board::at(index_on));
}

void shoot::play_bullet_animation(size_t from_index, size_t to_index)
{
	animation::player<animation::flash_bitmap>::launch
		(animation::flash_bitmap(to_index, std::chrono::milliseconds(50), "shoot.png"));
	animation::base_player::play();
	animation::player<animation::move>::launch
		(animation::move(from_index, to_index, typeid(*this)));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch
		(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();
}

void shoot::refresh_usable()
{
	bullets_ = bullets_n;
}