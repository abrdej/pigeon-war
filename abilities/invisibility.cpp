#include "invisibility.h"
#include "managers/entity_manager.h"
#include "core/board.h"
#include "entities/saberhand.h"
#include "core/states.h"
#include "gui/bitmap_center.h"

invisibility::invisibility(size_t id)
	: entity_id(id)
{

}

void invisibility::prepare(size_t for_index)
{
	states::state_controller::actual_state_ = states::states_types::wait_for_action;
	states::state_controller::possible_movements_.push_back(for_index);
	states::state_controller::actual_targeting_type_ = states::target_types::caster;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void invisibility::use(size_t on_index)
{
	if (used_)
        return;

    used_ = true;

    hide_me();

	receiver = turn::turn_system::every_round([this]() {
        ++turn_counter_;

        if (turn_counter_ == 2) {
            show_me();
            receiver.reset();
        }
    });
}

void invisibility::hide_me()
{
	index = board::index_for(entity_id);

	auto drawer = drawing_manager::typed_drawer_for<entity_drawer>(entity_id);
	drawer->change_bitmap(bitmap_key::saberhand_transparency);

    healths_manager::set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	auto drawer = drawing_manager::typed_drawer_for<entity_drawer>(entity_id);
	drawer->change_bitmap(bitmap_key::saberhand);

    healths_manager::set_destructible(entity_id, true);
}