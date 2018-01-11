#include "pigeon_war_client.h"
#include "gui/drawer.h"
#include "gui/view_constants.h"
#include "animation/animations_objects.h"
#include <algorithm>
#include <chrono>
#include <core/board.h>
#include <common/turn_status.h>
#include <managers/health_manager.h>
#include <common/message_types.h>
#include "caller.h"
#include "requests.h"
#include "animations_service.h"

using view::pigeon_war_client;

pigeon_war_client::pigeon_war_client()
		: window_(sf::VideoMode(1000, 700), "Turn based!") //, sf::Style::Fullscreen),
{
	board_drawer_ = std::make_unique<board_drawer>(this->state, this->lstate, window_);

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
	auto status = socket.connect("127.0.0.1", 8081);
	if (status != sf::Socket::Done) {
		std::cout << "Socket connecting error\n";
	}

	selector.add(socket);

	while (window_.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		receive_messages();
		update();
	}
}

void pigeon_war_client::receive_messages() {

	while (selector.wait(sf::milliseconds(5))) {

		sf::Packet packet;
		socket.receive(packet);

		message_types message;
		packet >> message;

		if (message == message_types::player_id) {
			unpack(packet, player_id);

			std::cout << "client player id: " << player_id << "\n";

		} else if (message == message_types::board) {
			unpack(packet, state.board.fields_);

		} else if (message == message_types::entities_bitmaps) {
			unpack(packet, state.entities_bitmaps);

			for (auto&& bitmap_pack : state.entities_bitmaps) {
				drawing_manager::add_component(bitmap_pack.first, std::make_shared<entity_drawer>(bitmap_pack.first, bitmap_pack.second));
			}

		} else if (message == message_types::healths) {
			unpack(packet, state.healths);

		} else if (message == message_types::end_turn) {

			std::size_t active_player_id;
			unpack(packet, active_player_id);

		} else if (message == message_types::animations) {

			unpack(packet, state.animations_queue);

			for (auto&& animation_pack : state.animations_queue) {
				if (animation_pack.animation_type == animation_types::move) {

					std::cout << "move animation\n";

					int from_index = animation_pack.x;
					int to_index = animation_pack.y;
					int entity_id = animation_pack.z;
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

					int from_index = animation_pack.x;
					int time = animation_pack.y;
					auto btm_key = animation_pack.btm_key;

					animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(from_index, std::chrono::milliseconds(time), btm_key));
					animation::base_player::play();

				} else if (animation_pack.animation_type == animation_types::change_health) {

					int to_index = animation_pack.x;
					int change_health = animation_pack.y;

					animation::player<animation::change_health>::launch(animation::change_health(to_index, change_health));
					animation::base_player::play();

				} else if (animation_pack.animation_type == animation_types::hide_show) {

					int index = animation_pack.x;
					int hide_show = animation_pack.y;
					int entity_id = animation_pack.z;

					if (hide_show == 0) {
						state.board.take(index);
					} else {
						state.board.give_back(entity_id, index);
					}
				} else if (animation_pack.animation_type == animation_types::change_bitmap) {
					int entity_id = animation_pack.x;
					auto new_bitmap = animation_pack.btm_key;

					drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(new_bitmap);
				}
			}

		} else if (message == message_types::game_state) {

			unpack(packet, state);

			update_for_entity();

		} else if (message == message_types::local_state) {

			unpack(packet, lstate);

			update_for_entity();

		} else if (message == message_types::description) {

			std::string description;
			unpack(packet, description);

			set_description(description);

		} else if (message == message_types::animation) {
			animations_service::handle(packet, state);
		}
	}
}

void pigeon_war_client::update()
{
	try {

		sf::Event event{};
		while (window_.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window_.close();
			}

			else if (event.type == sf::Event::MouseButtonReleased) {

				bool left = event.mouseButton.button == sf::Mouse::Button::Left;

				sf::Vector2i mouse_position(event.mouseButton.x, event.mouseButton.y);
				on_mouse_click(mouse_position, left);
			}
		}

	} catch (...) {

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

void pigeon_war_client::on_mouse_click(const point_type& args, bool left)
{
	if (board_panel_.is_hit(args))
	{
		auto hit_field = board_panel_.hit_field(args);
		on_board(hit_field.first, hit_field.second);
	}
	else if (buttons_panel_.is_hit(args))
	{
		size_t hit_button = buttons_panel_.hit_button(args);

		if (left) {
			on_button(hit_button);
		} else {
			get_button_description(hit_button);
		}
	}
}

void pigeon_war_client::on_board(size_t col, size_t row)
{
	if (!block) {
		block = true;

		call_on_board(socket, player_id, col, row);

		block = false;
	}
}

void pigeon_war_client::on_button(size_t n)
{
	call_on_button(socket, player_id, n);
}

void pigeon_war_client::get_button_description(size_t n) {
	call_get_button_description(socket, player_id, n);
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
	if (lstate.selected_index == -1)
		return;

	buttons_panel_.set_for_entity_for(lstate.entity_name, lstate.button_bitmaps);

	auto this_entity_id = state.board.at(lstate.selected_index);

	std::string effects;

	for (auto&& effect : state.entities_additional_effects[this_entity_id]) {
		effects += effect;
		effects += "\n";
	}

	set_description(effects);
}

void pigeon_war_client::set_description(const std::string& desc) {
	buttons_panel_.set_description(desc);
}
