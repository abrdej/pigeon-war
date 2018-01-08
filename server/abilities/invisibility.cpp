#include "invisibility.h"
#include "managers/entity_manager.h"
#include "core/board.h"
#include "entities/saberhand.h"
#include "core/states_controller.h"
#include "gui/bitmap_center.h"

invisibility::invisibility(size_t id)
	: entity_id(id)
{

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

	bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::saberhand_transparency;

    healths_manager::set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::saberhand;

    healths_manager::set_destructible(entity_id, true);
}