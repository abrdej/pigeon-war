#include "invisibility.h"
#include "managers/entity_manager.h"
#include "core/board.h"
#include "entities/saberhand.h"
#include "core/states.h"

invisibility::invisibility()
	: used_(false),
	turn_counter_(0),
	my_id_(-1)
{

}

void invisibility::prepare(size_t for_index)
{
	if (used_)
		return;

	states::state_controller::actual_state_ = states::states_types::wait_for_action;
	states::state_controller::possible_movements_.push_back(for_index);
	states::state_controller::actual_targeting_type_ = states::target_types::friendly;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void invisibility::use(size_t on_index)
{
	used_ = true;

/*	end_turn_receiver_ = event_center<events::event_end_turn>::add_receiver(
		std::make_shared<std::function<void()>>([this, on_index]()
	{
		++turn_counter_;
		if (turn_counter_ == 1)
		{
			hide_me(on_index);
		}
		else if (turn_counter_ == 2)
		{
			show_me(on_index);
		}
		else
			end_turn_receiver_ = nullptr;
	}));*/
}

void invisibility::hide_me(size_t my_index)
{
	my_id_ = board::take(my_index);
}

void invisibility::show_me(size_t my_index)
{
	board::give_back(my_id_, my_index);
}