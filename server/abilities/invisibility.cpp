#include "invisibility.h"
#include "managers/entity_manager.h"
#include "core/board.h"
#include "entities/saberhand.h"
#include "core/states_controller.h"
#include "sender.h"
#include "common/animations.h"

invisibility::invisibility(std::uint32_t id)
	: entity_id(id)
{

}

void invisibility::use(std::uint32_t on_index)
{
	if (used_)
        return;

    hide_me();

	invisibility_callback = make_after_n_round_callback_holder(duration, [this]() {
		show_me();
    });

	used_ = true;
}

void invisibility::hide_me()
{
	index = board::index_for(entity_id);

	sender::send(message_types::animation, animation_def::set_invisibility, entity_id);

    set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	sender::send(message_types::animation, animation_def::remove_invisibility, entity_id);

    set_destructible(entity_id, true);
}

std::string invisibility::hint() const {

	std::string desc;

	desc = "Invisibility - saberhand becomes invisible and can't receive any damage\n"
				   " through " + std::to_string(duration) + " turns.\n"
			"This ability can be used only once per battle\n";

	return std::move(desc);
}