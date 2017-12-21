#include <gui/drawing_manager.h>
#include <core/animations_queue.h>
#include "shoot.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

shoot::shoot()
	: bullets(bullets_n)
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
		range);
	
	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void shoot::use(size_t index_on)
{
	if (bullets == 0)
		return;

	--bullets;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

    play_animation(entity_id, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));
}

void shoot::play_animation(std::size_t entity_id, size_t from_index, size_t to_index)
{
	animations_queue::push_animation(animation_types::move,
									 from_index,
									 to_index,
									 -1,
									 bitmap_key::shoot);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 to_index,
									 150,
									 0,
									 bitmap_key::bum);
}

void shoot::refresh_usable()
{
	bullets = bullets_n;
}