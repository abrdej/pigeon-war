#include "tongue_of_fire.h"

#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

tongue_of_fire::tongue_of_fire()
	: used(false)
{
	onEveryRound([this]() {
		refresh_usable();
	});
}

void tongue_of_fire::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
		states::state_controller::possible_movements_costs_, range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void tongue_of_fire::use(size_t index_on)
{
	if (used)
		return;

	used = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	play_bullet_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	// show damage animation // for example. -9 dmg
}

void tongue_of_fire::play_bullet_animation(size_t from_index, size_t to_index)
{
	animations_queue::push_animation(animation_types::move,
									 from_index,
									 to_index,
									 -1,
									 bitmap_key::tongue_of_fire);
}

void tongue_of_fire::refresh_usable()
{
	used = false;
}