#include "gui.h"

#include "view_constants.h"
#include "core/game.h"
#include "drawer.h"
#include "animation/animations_objects.h"
#include <algorithm>
#include <chrono>

namespace view
{
gui::gui(game& g)
		: window_(sf::VideoMode(1000, 700), "Turn based!"), //, sf::Style::Fullscreen),
		  game_(g)
{
	board_drawer_ = std::make_unique<board_drawer>(game_, window_);

	board_panel_.prepare();
	buttons_panel_.prepare();
	//labels_panel_.prepare(fm_);
	prepare_animations();

	animation_player_impl_.updater([this]()
								   {
									   return update();
								   });
}

gui::~gui()
{
}

void gui::run()
{
	while (window_.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		update();
	}
}

void gui::update()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			auto mouse_position = sf::Mouse::getPosition(window_);
			on_mouse_click(mouse_position);
		}

//		if (event.type == sf::Event::MouseMoved) {
//
//			auto mouse_position = sf::Mouse::getPosition(window_);
//			if (buttons_panel_.is_hit(mouse_position)) {
//				size_t hit_button = buttons_panel_.hit_button(mouse_position);
//                buttons_panel_.set_hint_for(sf::Vector2f(mouse_position), hit_button);
//			} else {
//                buttons_panel_.remove_hint();
//            }
//
//		}
	}

	window_.clear();
	draw(window_);
	window_.display();
}

void gui::draw(sf::RenderWindow& window)
{
	board_panel_.draw(window);
	buttons_panel_.draw(window);
	board_drawer_->draw();
	entities_renderer_.render(window);
	animation_player_impl_.draw(window);
}

void gui::on_mouse_click(const point_type& args)
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

void gui::on_board(size_t col, size_t row)
{
	if (!block) {
		block = true;
		game_.on_board(col, row);
		update_for_entity();
		block = false;
	}
}

void gui::on_button(size_t n)
{
	game_.on_button(n);
	update_for_entity();
}

void gui::prepare_animations()
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

void gui::update_for_entity()
{
	auto selected_index = states::state_controller::selected_index_;
	if (selected_index == -1)
		return;

	auto entity_id = board::at(selected_index);

	buttons_panel_.set_buttons_for(entity_id);
	buttons_panel_.set_name_for(entity_id);
}
};