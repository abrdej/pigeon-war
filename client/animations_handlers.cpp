#include <core/board.h>
#include "animations_handlers.h"

void magic_bullet_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 from_index, to_index;
	unpack(packet, from_index);
	unpack(packet, to_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   bitmap_key::monk_use_1));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   bitmap_key::monk_use_2));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   bitmap_key::monk_use_3));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::magic_splash));
	animation::base_player::play();
}

void teleport_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 from_index, to_index;
	unpack(packet, from_index);
	unpack(packet, to_index);

	auto entity_id = g_state.board.take(from_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   bitmap_key::teleport));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::teleport));
	animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);
}

void drain_handler::handle(sf::Packet& packet, game_state& g_state) {
	move_with_return_base_handler::handle(packet, g_state);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::healthing));
	animation::base_player::play();
}

void grenade_handler::handle(sf::Packet& packet, game_state& g_state) {

	shot_base_handler::handle(packet, g_state);

	auto from_cr = board::to_pos(to_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   bitmap_key::detonation_anim));
	animation::base_player::play();
}

void flame_thrower_handler::handle(sf::Packet& packet, game_state& g_state) {

	shot_base_handler::handle(packet, g_state);

	auto from_cr = board::to_pos(to_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   bitmap_key::detonation_anim));
	animation::base_player::play();
}

void giant_ram_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 from_index, to_index;
	unpack(packet, from_index);
	unpack(packet, to_index);

	auto entity_id = g_state.board.take(from_index);

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(bitmap_key::giant_ram);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
	animation::base_player::play();

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(bitmap_key::giant);

	g_state.board.give_back(entity_id, to_index);
}

void kill_handler::handle(sf::Packet& packet, game_state& g_state) {
	sf::Uint64 from_index, to_index, enemy_index;
	unpack(packet, from_index);
	unpack(packet, to_index);
	unpack(packet, enemy_index);

	auto entity_id = g_state.board.take(from_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::killer_jump));
	animation::base_player::play();

	animation::player<animation::move>::launch(animation::move(to_index, enemy_index, entity_id));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(enemy_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::killer_attack));

	animation::player<animation::move>::launch(animation::move(enemy_index, to_index, entity_id));
	animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);
}

void spider_web_handler::handle(sf::Packet& packet, game_state& g_state) {
	shot_base_handler::handle(packet, g_state);

	sf::Uint64 land_index;
	unpack(packet, land_index);

	auto enemy_id = g_state.board.take(to_index);

	if (to_index != land_index) {

		animation::player<animation::move>::launch(animation::move(to_index, land_index, bitmap_key::spider_web));
		animation::base_player::play();
	}

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(land_index,
																			   std::chrono::milliseconds(150),
																			   bitmap_key::spider_web));
	animation::base_player::play();

	g_state.board.give_back(enemy_id, land_index);
}

void spiral_of_fire_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 from_index, to_index;
	unpack(packet, from_index);
	unpack(packet, to_index);

	auto entity_id = g_state.board.take(from_index);

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(bitmap_key::spiral_of_fire);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
	animation::base_player::play();

	animation::player<animation::move>::launch(animation::move(to_index, from_index, entity_id));
	animation::base_player::play();

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(bitmap_key::creature);

	g_state.board.give_back(entity_id, from_index);
}

void sword_blow_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 index;
	unpack(packet, index);

	auto entity_id = g_state.board.take(index);

	auto from_cr = board::to_pos(index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   bitmap_key::samurai_rat_sword));

	g_state.board.give_back(entity_id, index);
}

void bludgeon_push_handler::handle(sf::Packet& packet, game_state& g_state) {

	sf::Uint64 from_index, to_index, push_index;
	unpack(packet, from_index);
	unpack(packet, to_index);
	unpack(packet, push_index);

	auto caster_id = g_state.board.take(from_index);

	animation::player<animation::move_entity>::launch(animation::move_entity(from_index, to_index, caster_id));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), bitmap_key::bum));
	animation::base_player::play();

	g_state.board.give_back(caster_id, to_index);
	auto enemy_id = g_state.board.take_bottom(to_index);

	animation::player<animation::move_entity>::launch(animation::move_entity(to_index, push_index, enemy_id));
	animation::base_player::play();

	g_state.board.give_back(enemy_id, push_index);
}

void rage_handler::handle(sf::Packet& packet, game_state& g_state) {
	sf::Uint64 index;
	unpack(packet, index);

	auto entity_id = g_state.board.take(index);

	auto from_cr = board::to_pos(index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   bitmap_key::troll_rage));

	g_state.board.give_back(entity_id, index);
}