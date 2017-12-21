#include "drain.h"

#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "managers/health_manager.h"

drain::drain()
{
	onEveryRound([this]() {
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
	auto entity_id = board::at(used_from_index);

	play_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(damage_pack(damage,
													   damage_types::MELEE,
													   board::at(index_on),
													   entity_id));

	healths_manager::receive_damage(healing(drain_amount,
											entity_id));
	used = true;
}

void drain::play_animation(size_t index_from, size_t index_on)
{
	auto entity_id = board::take(index_from);

	animations_queue::push_animation(animation_types::move, index_from, index_on, entity_id, bitmap_key::none);
	animations_queue::push_animation(animation_types::flash_bitmap, index_on, 150, 0, bitmap_key::native_attack);
	animations_queue::push_animation(animation_types::move, index_on, index_from, entity_id, bitmap_key::none);

	board::give_back(entity_id, index_from);

	animations_queue::push_animation(animation_types::flash_bitmap, index_from, 150, 0, bitmap_key::healthing);
}