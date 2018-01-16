#include <gui/drawing_manager.h>
#include <core/animations_queue.h>
#include <common/message_types.h>
#include "shoot.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

shoot::shoot()
		: bullets(bullets_n)
{
	onEveryRound([this]() {
		bullets = bullets_n;
	});
}

std::string shoot::hint() const {

	std::string desc;
	desc = "Shoot - the shooter can give a double shot of: " +
		   std::to_string(damage) + " damage.\n" +
		   "Remaining shots: " + std::to_string(bullets) +
		   "\nRange: " + std::to_string(range) + ".";
	return std::move(desc);
}

void shoot::use(std::uint32_t index_on)
{
	if (bullets == 0)
		return;

	--bullets;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	sender::send(message_types::animation, animation_def::shoot, used_from_index, index_on);

	damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));
}