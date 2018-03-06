#include "pigeon_war_client.h"
#include "gui/drawer.h"
#include "gui/view_constants.h"
#include "animation/animations_objects.h"
#include <algorithm>
#include <chrono>
#include <core/board.h>
#include <common/turn_status.h>
#include <common/message_types.h>
#include <gui/drawer_factory.h>
#include <common/messages/messages.h>
#include "caller.h"
#include "requests.h"
#include "animations_service.h"

using view::pigeon_war_client;

pigeon_war_client::pigeon_war_client(const std::string& address, int port)
		: window_(sf::VideoMode(1000, 700), "Turn based!"),
		  address(address),
		  port(port) {

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
	std::cout << "Waiting for game...\n";

	//sf::TcpSocket matching_socket;

	//auto status = matching_socket.connect(address, port);
	//bool matching = true;
	//std::int32_t game_port = port;

	//if (status != sf::Socket::Done) {
	//	std::cout << "Matching server connecting error\n";
	//	matching = false;

	//} else {

	//	sf::Packet packet;
	//	matching_socket.receive(packet);

		//message_types message;
		//packet >> message;

		//if (message != message_types::game_server_port) {
		//	std::cout << "bad message\n";
		//}

		//packet >> game_port;

		//std::cout << "Game port: " << std::to_string(game_port) << "\n";
	//}

	auto status = socket.connect(address, port);

	if (status != sf::Socket::Done) {
		std::cout << "Game server connecting error: " << status << "\n";
	}

	std::cout << "Connected to game\n";

	selector.add(socket);

	while (window_.isOpen()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		receive_messages();
		update();
	}
}

void pigeon_war_client::receive_messages() {

	while (selector.wait(sf::milliseconds(5))) {

		sf::Packet packet;
		socket.receive(packet);

		std::string message;
		packet >> message;

		std::cout << message << "\n";

		try {

			using nlohmann::json;
			json data = json::parse(message);

			if (data.count("client_id")) {
				player_id = data["client_id"];

			} else if (data.count("map_name")) {
				std::string map_name;
				map_name = data["map_name"];
				window_.setTitle(map_name);

			} else if (data.count("board")) {
				state.board.fields_ = data["board"];

			} else if (data.count("entities_names")) {
				json_to_unordered_map(data["entities_names"], state.entities_names);

				for (auto&& names_pack : state.entities_names) {
					drawing_manager::add_component(names_pack.first, drawer_factory::create(names_pack.first, names_pack.second));
				}

			} else if (data.count("entities_healths")) {
				json_to_unordered_map(data["entities_healths"], state.healths);

			} else if (data.count("end_turn")) {
				std::uint32_t active_player_id = data["end_turn"];
				std::cout << "end_turn: " << active_player_id << "\n";

			} else if (data.count("game_state")) {
				state = data["game_state"];
				update_for_entity();

			} else if (data.count("local_state")) {
				from_json(data["local_state"], lstate);
				update_for_entity();

			} else if (data.count("description")) {
				std::string description = data["description"];
				desc_pos = sf::Mouse::getPosition(window_);
				hint_ptr = std::make_unique<hint>(desc_pos, description);

			} else if (data.count("animation")) {
				animations_service::handle(data, state);
			}

		} catch (nlohmann::detail::parse_error&) {

			std::cout << "Parse error in: " << message << "\n";

		} catch (nlohmann::detail::type_error&) {

            std::cout << "Type error in: " << message << "\n";

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

			if (hint_ptr) {
				auto len = std::sqrt(std::pow(desc_pos.x - sf::Mouse::getPosition(window_).x, 2.) +
											 std::pow(desc_pos.y - sf::Mouse::getPosition(window_).y, 2.));

				const float len_th = 35.f;
				if (len > len_th) {
					hint_ptr = nullptr;
				}
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

	if (hint_ptr)
		hint_ptr->draw(window);
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
		std::uint32_t hit_button = buttons_panel_.hit_button(args);

		if (left) {
			on_button(hit_button);
		} else {
			get_button_description(hit_button);
		}
	}
}

void pigeon_war_client::on_board(std::uint32_t col, std::uint32_t row)
{
	if (!block) {
		block = true;

		call_on_board(socket, player_id, col, row);

		block = false;
	}
}

void pigeon_war_client::on_button(std::uint32_t n)
{
	call_on_button(socket, player_id, n);
}

void pigeon_war_client::get_button_description(std::uint32_t n) {
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

	auto entity_id = state.board.at(lstate.selected_index);

	buttons_panel_.set_for_entity_for(entity_id, lstate.entity_name, lstate.button_bitmaps);

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
