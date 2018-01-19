#include <common/message_types.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include <common/animations.h>
#include <sender.h>
#include "cure.h"

cure::cure(std::uint32_t entity_id) : entity_id(entity_id) {}


void cure::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	auto friend_id = board::at(index_on);

//	sender::send(message_types::animation, animation_def::drain, used_from_index, index_on);

	entity_manager::get(friend_id).get<damage_taker>()->heal(healing(cure_amount,
																	 friend_id));
	used = true;
}