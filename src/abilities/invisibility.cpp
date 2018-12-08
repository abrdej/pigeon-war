#include "invisibility.h"

#include <components/damage_taker.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <entities/saberhand.h>
#include <managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <server/sender.h>

invisibility::invisibility(std::uint32_t id)
	: entity_id(id) {}

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
	index = game_board().index_for(entity_id);

	sender::send(make_action_message("set_invisibility", entity_id));

    set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	sender::send(make_action_message("remove_invisibility", entity_id));

    set_destructible(entity_id, true);
}