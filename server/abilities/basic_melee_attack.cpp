#include "basic_melee_attack.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"

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
	auto caster_id = board::at(used_from_index);

	play_animation(used_from_index, index_on);

	auto enemy_id = board::at(index_on);

	damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

	used = true;

	// show damage animation // for example. -9 dmg
	//states::state_controller::target_fields(states::target_types::non);
}

void basic_melee_attack::play_animation(size_t index_from, size_t index_on)
{
	auto entity_id = board::take(index_from);

	animations_queue::push_animation(animation_types::move,
									 index_from,
									 index_on,
									 entity_id,
									 bitmap_key::none);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 index_on,
									 150,
									 0,
									 bitmap_key::claws);

	animations_queue::push_animation(animation_types::move,
									 index_on,
									 index_from,
									 entity_id,
									 bitmap_key::none);

	board::give_back(entity_id, index_from);
}