//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_MESSAGE_TYPES_H
#define PIGEONWAR_MESSAGE_TYPES_H

#include <unordered_map>

enum class message_types {
	game_server_port,
	player_id,
	board,
	entities_bitmaps,
	entities_names,
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
	get_effect,
	map_name
};

struct message_types_key_hash
{
	template <typename T>
	std::uint32_t operator()(T t) const
	{
		return static_cast<std::uint32_t>(t);
	}
};

struct message_type_to_string {
	static std::string convert() {
		static const std::unordered_map<message_types, std::string, message_types_key_hash> map = {
				{message_types::player_id, "player_id"},
				{message_types::board, "board"},
				{message_types::entities_bitmaps, "entities_bitmaps"},
				{message_types::healths, "healths"},
				{message_types::end_turn, "end_turn"},
				{message_types::animations, "animations"},
				{message_types::game_state, "game_state"},
				{message_types::local_state, "local_state"},
				{message_types::description, "description"},
				{message_types::animation, "animation"},
				{message_types::on_button, "on_button"},
				{message_types::on_board, "on_board"},
				{message_types::get_button_description, "get_button_description"},
				{message_types::get_effect, "get_effect"}
		};
	}
};

#endif //PIGEONWAR_MESSAGE_TYPES_H
