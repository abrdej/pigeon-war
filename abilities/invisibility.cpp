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
	used_ = true;

    hide_me();

	receiver = turn::turn_system::every_turn(std::make_shared<std::function<void()>>([this](){
			++turn_counter_;

			//if (turn_counter_ == 1) {
			//	hide_me();
			//}
			if (turn_counter_ == 3) {
				show_me();
				receiver.reset();
			}
	}));
}

void invisibility::hide_me()
{
	index = board::index_for(entity_id);

	view::bitmap_center::change_entity_image<saberhand>("saberhand_transparency.png");

    healths_manager::set_destructible(entity_id, false);
}

void invisibility::show_me()
{
	view::bitmap_center::change_entity_image<saberhand>("saberhand.png");
    healths_manager::set_destructible(entity_id, true);
}