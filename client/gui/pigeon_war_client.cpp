#include "pigeon_war_client.h"
#include "drawer.h"
#include "view_constants.h"
#include "animation/animations_objects.h"
#include <algorithm>
#include <chrono>
#include <core/board.h>

namespace view
{
pigeon_war_client::pigeon_war_client()
		: window_(sf::VideoMode(1000, 700), "Turn based!") //, sf::Style::Fullscreen),
{
	board_drawer_ = std::make_unique<board_drawer>(this->state, window_);

	board_panel_.prepare();
	buttons_panel_.prepare();
	prepare_animations();

	animation_player_impl_.updater([this]()
								   {
									   return update();
								   });
}

void pigeon_war_client::run()
{
	client = std::make_unique<rpc::client>("127.0.0.1", 8080);

	// this will fill state of game
	state.board.fields_ = client->call("get_board").as<std::array<std::vector<std::size_t>, board::cols_n * board::rows_n>>();

	state.entities_bitmaps = client->call("get_entities_bitmaps").as<decltype(state.entities_bitmaps)>();

	state.healths = client->call("get_entities_healths").as<decltype(state.healths)>();

	for (auto&& bitmap_pack : state.entities_bitmaps) {
		drawing_manager::add_component(bitmap_pack.first, std::make_shared<entity_drawer>(bitmap_pack.first, bitmap_pack.second));
	}

	std::cout << "client initialized\n";

	while (window_.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		update();
	}
}

void pigeon_war_client::update()
{
	sf::Event event{};
	while (window_.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window_.close();
		}

		else if (event.type == sf::Event::MouseButtonReleased) {

			sf::Vector2i mouse_position(event.mouseButton.x, event.mouseButton.y);
			on_mouse_click(mouse_position);
		}
	}

	window_.clear();
	draw(window_);
	window_.display();
}

void pigeon_war_client::draw(sf::RenderWindow& window)
{
	board_panel_.draw(window);
	buttons_panel_.draw(window);
	board_drawer_->draw();
	entities_renderer_.render(window, state.board, state.healths);
	animation_player_impl_.draw(window);
}

void pigeon_war_client::on_mouse_click(const point_type& args)
{
	if (board_panel_.is_hit(args))
	{
		auto hit_field = board_panel_.hit_field(args);
		on_board(hit_field.first, hit_field.second);
	}
	else if (buttons_panel_.is_hit(args))
	{
		size_t hit_button = buttons_panel_.hit_button(args);
		on_button(hit_button);
	}
}

void pigeon_war_client::on_board(size_t col, size_t row)
{
	if (!block) {
		block = true;

		client->call("on_board", col, row);

		state.animations_queue = client->call("pull_animations").as<decltype(state.animations_queue)>();

		for (auto&& animation_pack : state.animations_queue) {
			if (animation_pack.animation_type == animation_types::move) {

				std::cout << "move animation\n";

				short from_index = std::get<0>(animation_pack.tup);
				short to_index = std::get<1>(animation_pack.tup);
				short entity_id = std::get<2>(animation_pack.tup);
				auto btm_key = animation_pack.btm_key;

				if (entity_id != -1) {
					state.board.take(from_index);

					animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
					animation::base_player::play();

					state.board.give_back(entity_id, to_index);

				} else {
					animation::player<animation::move>::launch(animation::move(from_index, to_index, btm_key));
					animation::base_player::play();
				}
			} else if (animation_pack.animation_type == animation_types::flash_bitmap) {

				short from_index = std::get<0>(animation_pack.tup);
				short time = std::get<1>(animation_pack.tup);
				auto btm_key = animation_pack.btm_key;

				animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index, std::chrono::milliseconds(time), btm_key));
				animation::base_player::play();
			}
		}

		state = client->call("get_game_state").as<decltype(state)>();

		update_for_entity();
		block = false;
	}
}

void pigeon_war_client::on_button(size_t n)
{
	client->call("on_button", n);

	state.animations_queue = client->call("pull_animations").as<decltype(state.animations_queue)>();

	state = client->call("get_game_state").as<decltype(state)>();

	update_for_entity();
}

void pigeon_war_client::prepare_animations()
{
	animation::base_player::starter([this]()
									{
										return animation_player_impl_.run();
									});
	animation::player<animation::move>::connect([this](animation::move move_data)
												{
													return animation::prepare_animation<animation::move_object_animation>(animation_player_impl_, move_data);
												});
	animation::player<animation::move_entity>::connect([this](animation::move_entity move_data)
													   {
														   return animation::prepare_animation<animation::move_object_animation2>(animation_player_impl_, move_data);
													   });
	animation::player<animation::flash_bitmap>::connect([this](animation::flash_bitmap flash_bitmap_data)
														{
															return animation::prepare_animation<animation::flash_bitmap_animation>(animation_player_impl_, flash_bitmap_data);
														});
	animation::player<animation::change_health>::connect([this](animation::change_health change_health_data)
														 {
															 return animation::prepare_animation<animation::change_health_animation>(animation_player_impl_, change_health_data);
														 });
}

void pigeon_war_client::update_for_entity()
{
	if (state.selected_index == -1)
		return;

	auto entity_id = state.board.at(state.selected_index);

	buttons_panel_.set_for_entity_for(state.entity_name, state.button_bitmaps);
}
};