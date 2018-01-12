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

    hide_me();

	receiver = turn::turn_system::every_turn([this]() {

        if (++turn_counter_ == 2 * duration) {
            show_me();
            receiver.reset();
        }
    });

	used_ = true;
}

void invisibility::hide_me()
{
	index = board::index_for(entity_id);

	bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::saberhand_transparency;

	sender::send(message_types::animation, animation_def::set_invisibility, entity_id);

    healths_manager::set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	bitmap_field_manager::component_for(entity_id).bmt_key = bitmap_key::saberhand;

	sender::send(message_types::animation, animation_def::remove_invisibility, entity_id);

    healths_manager::set_destructible(entity_id, true);
}

std::string invisibility::hint() const {

	std::string desc;

	desc = "Invisibility - saberhand becomes invisible and can't receive any damage\n"
				   " through " + std::to_string(duration) + " turns.\n"
			"This ability can be used only once per battle\n";

	return std::move(desc);
}