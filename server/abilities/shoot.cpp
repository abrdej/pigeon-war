#include <gui/drawing_manager.h>
#include <common/message_types.h>
#include <fstream>
#include <common/make_message.h>
#include "shoot.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"
#include "common/logging.h"
#include "descriptions.h"

shoot::shoot()
		: bullets(bullets_n)
{
	on_every_two_turns_from_next([this]() {
		bullets = bullets_n;
        LOG_DEBUG() << "shoot refresh bullets count to: " << bullets << "\n";
	});
}

void shoot::use(std::uint32_t index_on)
{
	if (bullets == 0) {
		LOG_DEBUG() << "bullets == 0" << "\n";
		return;
	}

	--bullets;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	LOG_DEBUG() << "shoot used from pos: " << board::to_pos(used_from_index) << "\n";
	LOG_DEBUG() << "by entity of id: " << entity_id << "\n";
	LOG_DEBUG() << "to pos: " << board::to_pos(index_on) << "\n";
    LOG_DEBUG() << "remaining bullets: " << bullets << "\n";

	sender::send(make_action_message("shoot", used_from_index, index_on));

	auto final_damage = damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

	LOG_DEBUG() << "dealt damage of: " << final_damage << "\n";
}