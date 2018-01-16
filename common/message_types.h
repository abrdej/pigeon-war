//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_MESSAGE_TYPES_H
#define PIGEONWAR_MESSAGE_TYPES_H

#include "add_enum.h"

enum class message_types {
	player_id,
	board,
	entities_bitmaps,
	healths,
	end_turn,
	animations,
	game_state,
	local_state,
	description,
	animation,
	on_button,
	on_board,
	get_button_description,
	get_effect
};

struct message_types_key_hash
{
	template <typename T>
	std::uint64_t operator()(T t) const
	{
		return static_cast<std::uint64_t>(t);
	}
};

PACKET_ADD_ENUM(message_types)

#endif //PIGEONWAR_MESSAGE_TYPES_H
