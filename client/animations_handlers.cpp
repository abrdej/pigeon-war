#include <core/board.h>
#include "animations_handlers.h"

void magic_bullet_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
	extract(data, from_index, to_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "monk_use_1));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "monk_use_2));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "monk_use_3));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   "magic_splash));
	animation::base_player::play();
}

void teleport_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
	extract(data, from_index, to_index);

	auto entity_id = g_state.board.take(from_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "teleport));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   "teleport));
	animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);
}

void drain_handler::handle(nlohmann::json& data, game_state& g_state) {
	move_with_return_base_handler::handle(data, g_state);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(150),
																			   "healthing));
	animation::base_player::play();
}

void grenade_handler::handle(nlohmann::json& data, game_state& g_state) {

	shot_base_handler::handle(data, g_state);

	auto from_cr = board::to_pos(to_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   "detonation_anim));
	animation::base_player::play();
}

void flame_thrower_handler::handle(nlohmann::json& data, game_state& g_state) {

	shot_base_handler::handle(data, g_state);

	auto from_cr = board::to_pos(to_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   "detonation_anim));
	animation::base_player::play();
}

void giant_ram_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
	extract(data, from_index, to_index);

	auto entity_id = g_state.board.take(from_index);

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap("giant_ram);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
	animation::base_player::play();

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap("giant);

	g_state.board.give_back(entity_id, to_index);
}

void saw_passing_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
	extract(data, from_index, to_index);

	auto entity_id = g_state.board.take(from_index);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
	animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);
}

void kill_handler::handle(nlohmann::json& data, game_state& g_state) {
	std::uint32_t from_index, to_index, enemy_index;
	extract(data, from_index, to_index, enemy_index);

	auto entity_id = g_state.board.take(from_index);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   "killer_jump));
	animation::base_player::play();

	animation::player<animation::move>::launch(animation::move(to_index, enemy_index, entity_id));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(enemy_index,
																			   std::chrono::milliseconds(150),
																			   "killer_attack));

	animation::player<animation::move>::launch(animation::move(enemy_index, to_index, entity_id));
	animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);
}

void spider_web_handler::handle(nlohmann::json& data, game_state& g_state) {
	shot_base_handler::handle(data, g_state);

	std::uint32_t land_index;
	extract(data, land_index);

	auto enemy_id = g_state.board.take(to_index);

	if (to_index != land_index) {

		animation::player<animation::move>::launch(animation::move(to_index, land_index, "spider_web));
		animation::base_player::play();
	}

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(land_index,
																			   std::chrono::milliseconds(150),
																			   "spider_web));
	animation::base_player::play();

	g_state.board.give_back(enemy_id, land_index);
}

void spiral_of_fire_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
	extract(data, from_index, to_index);

	auto entity_id = g_state.board.take(from_index);

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap("spiral_of_fire);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
	animation::base_player::play();

	animation::player<animation::move>::launch(animation::move(to_index, from_index, entity_id));
	animation::base_player::play();

	drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap("creature);

	g_state.board.give_back(entity_id, from_index);
}

void sword_blow_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t index;
	extract(data, index);

	auto entity_id = g_state.board.take(index);

	auto from_cr = board::to_pos(index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   "samurai_rat_sword));
    animation::base_player::play();

	g_state.board.give_back(entity_id, index);
}

void bludgeon_push_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index, push_index;
	extract(data, from_index, to_index, push_index);

	auto caster_id = g_state.board.take(from_index);

	animation::player<animation::move_entity>::launch(animation::move_entity(from_index, to_index, caster_id));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum));
	animation::base_player::play();

	g_state.board.give_back(caster_id, to_index);
	auto enemy_id = g_state.board.take_bottom(to_index);

	animation::player<animation::move_entity>::launch(animation::move_entity(to_index, push_index, enemy_id));
	animation::base_player::play();

	g_state.board.give_back(enemy_id, push_index);
}

void rage_handler::handle(nlohmann::json& data, game_state& g_state) {
	std::uint32_t index;
	extract(data, index);

	auto entity_id = g_state.board.take(index);

	auto from_cr = board::to_pos(index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   "troll_rage));

	g_state.board.give_back(entity_id, index);
}

void change_health_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::int32_t to_index;
	std::int32_t change_health;

	extract(data, to_index, change_health);

	sf::Color color = change_health < 0 ? sf::Color(210, 20, 15) : sf::Color(15, 210, 20);
	color = (change_health == 0) ? sf::Color(15, 20, 210) : color;

	animation::player<animation::show_number_change>::launch(animation::show_number_change(to_index, change_health, color));
	animation::base_player::play();
}

void change_power_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::int32_t to_index;
	std::int32_t change_power;

	extract(data, to_index, change_power);

	animation::player<animation::show_number_change>::launch(animation::show_number_change(to_index, change_power, sf::Color::Blue));
	animation::base_player::play();
}

void portal_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t from_index, to_index;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> neighboring_moves;

	extract(data, from_index, to_index, neighboring_moves);

	//neighboring_moves = data[3];

	auto entity_id = g_state.board.take(from_index);

    std::vector<std::pair<std::uint32_t, std::uint32_t>> taken;

    for (auto&& move_pack : neighboring_moves) {
        auto neighboring_id = g_state.board.take(move_pack.first);
        taken.emplace_back(neighboring_id, move_pack.second);
    }

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "portal_1));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
																			   std::chrono::milliseconds(100),
																			   "portal_2));
	animation::base_player::play();

    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index,
                                                                               std::chrono::milliseconds(100),
                                                                               "portal_3));
    animation::base_player::play();

    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
                                                                               std::chrono::milliseconds(100),
                                                                               "portal_3));
    animation::base_player::play();

    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
                                                                               std::chrono::milliseconds(100),
                                                                               "portal_2));
    animation::base_player::play();

    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
                                                                               std::chrono::milliseconds(100),
                                                                               "portal_1));
    animation::base_player::play();

	g_state.board.give_back(entity_id, to_index);

    for (auto&& taken_pack : taken) {
        g_state.board.give_back(taken_pack.first, taken_pack.second);
    }
}

void destruction_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t index;
	extract(data, index);

	//auto entity_id = g_state.board.take(index);

	auto from_cr = board::to_pos(index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(75),
																			   "destruction_1));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
                                                                               std::chrono::milliseconds(75),
                                                                               "destruction_2));
    animation::base_player::play();
    animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
                                                                               std::chrono::milliseconds(75),
                                                                               "destruction_3));
    animation::base_player::play();

	//g_state.board.give_back(entity_id, index);
}

void fist_of_doom_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t to_index;
	extract(data, to_index);

	auto pos = board::to_pos(to_index);
	pos.second = 0;

	auto from_index = board::to_index(pos.first, pos.second);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, "fist_of_doom));
	animation::base_player::play();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(100), "fist_of_doom_ex));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(100), "fist_of_doom_ex2));
	animation::base_player::play();
}

void meteorite_handler::handle(nlohmann::json& data, game_state& g_state) {

	std::uint32_t to_index;
	extract(data, to_index);

	auto pos = board::to_pos(to_index);
	pos.second = 0;

	auto from_index = board::to_index(pos.first, pos.second);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, "meteorite));
	animation::base_player::play();

	auto from_cr = board::to_pos(to_index);
	from_cr.first -= 1;
	from_cr.second -= 1;

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
																			   std::chrono::milliseconds(150),
																			   "detonation_anim));
	animation::base_player::play();
}