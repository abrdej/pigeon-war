#include <gui/drawing_manager.h>
#include <managers/animation_manager.h>
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
	auto entity_id = board::at(used_from_index);

    play_animation(entity_id, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage_, board::at(index_on), entity_id));
}

void shoot::play_animation(std::size_t entity_id, size_t from_index, size_t to_index)
{
//	auto animator = animation_manager::animator_for<shooter_animator>(entity_id);
//	animator->set_shoot(std::chrono::milliseconds(50));
//	animation_manager::pull_animations();

//    animation_manager::push_animation(0.f, [this, entity_id]() {
//        auto drawer = drawing_manager::typed_drawer_for<shooter_drawer>(entity_id);
//        drawer->set_state(shooter_drawer::States::shoot);
//        std::cout << "shoot\n";
//    });
//    animation_manager::push_animation(0.1f, [this, entity_id]() {
//        auto drawer = drawing_manager::typed_drawer_for<shooter_drawer>(entity_id);
//        drawer->set_state(shooter_drawer::States::normal);
//        std::cout << "back to normal\n";
//    });
//    animation_manager::pull_animations();


//	animation::player<animation::flash_bitmap>::launch
//			(animation::flash_bitmap(to_index, std::chrono::milliseconds(50), "shoot.png"));
//	animation::base_player::play();
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