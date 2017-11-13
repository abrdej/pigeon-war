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
		game_.on_board(col, row);
		update_for_entity();
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
		//labels_panel_.set_labels_for(*entity);
	}
};

/*
namespace view
{
	using namespace nana;

	gui::gui(game& g)
		: fm_(rectangle(0, 0, 1500, 1000)),
		dw_(fm_),
		game_(g)
	{
		prepare_events();
		board_panel_.prepare();
		buttons_panel_.prepare();
		labels_panel_.prepare(fm_);
		prepare_timer();
		prepare_animations();

		dw_.draw([this](paint::graphics& graph)
		{
			draw(graph);
		});

		animation_player_impl_.updater([this]()
		{
			return update();
		});

		fm_.show();
	}

	gui::~gui()
	{
	}

	void gui::update()
	{
		dw_.update();
	}

	void gui::prepare_events()
	{
		fm_.events().mouse_move([this](const arg_mouse& args)
		{
			on_mouse_move(args);
		});
		fm_.events().dbl_click([this](const arg_mouse& args)
		{
			on_dbl_click(args);
		});
		fm_.events().mouse_up([this](const arg_mouse& args)
		{
			on_mouse_up(args);
		});
		fm_.events().mouse_down([this](const arg_mouse& args)
		{
			on_mouse_down(args);
		});
		fm_.events().click([this](const arg_mouse& args)
		{
			on_mouse_click(args);
		});
	}

	void gui::draw(paint::graphics& graph)
	{
		buttons_panel_.draw(graph);
		board_panel_.draw(graph);
		drawers::draw(game_, graph);
		animation_player_impl_.draw(graph);
	}

	void gui::on_mouse_move(const arg_mouse& args)
	{
	}

	void gui::on_dbl_click(const arg_mouse& args)
	{
		auto mouse_position = args.pos;
	}

	void gui::on_mouse_up(const nana::arg_mouse& args)
	{
	}

	void gui::on_mouse_click(const nana::arg_mouse& args)
	{
		if (board_panel_.is_hit(args.pos))
		{
			auto hit_field = board_panel_.hit_field(args.pos);
			on_board(hit_field.first, hit_field.second);
		}
		else if (buttons_panel_.is_hit(args.pos))
		{
			size_t hit_button = buttons_panel_.hit_button(args.pos);
			on_button(hit_button);
		}
	}

	void gui::on_mouse_down(const nana::arg_mouse& args)
	{

	}

	void gui::on_board(size_t col, size_t row)
	{
		game_.on_board(col, row);
		update_for_entity();
	}

	void gui::on_button(size_t n)
	{
		game_.on_button(n);
	}

	void gui::prepare_timer()
	{
		timer_.interval(100);
		timer_.elapse(std::bind(&gui::update, this));
		timer_.start();
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
		animation::player<animation::flash_bitmap>::connect([this](animation::flash_bitmap flash_bitmap_data)
		{
			return animation::prepare_animation<animation::flash_bitmap_animation>(animation_player_impl_, flash_bitmap_data);
		});
	}

	void gui::update_for_entity()
	{
		auto selected_index = states::state_controller::selected_index_;
		if (selected_index == -1)
			return;

		auto entity = game_.board_.at(selected_index);
		
		buttons_panel_.set_buttons_for(*entity);
		labels_panel_.set_labels_for(*entity);
	}
};

namespace view
{
	using namespace nana;

	gui::gui(game& g)
		: fm_(rectangle(0, 0, 1500, 1000)),
		dw_(fm_),
		game_(g)
	{
		prepare_events();
		board_panel_.prepare();
		buttons_panel_.prepare();
		labels_panel_.prepare(fm_);
		prepare_timer();
		prepare_animations();

		dw_.draw([this](paint::graphics& graph)
		{
			draw(graph);
		});

		animation_player_impl_.updater([this]()
		{
			return update();
		});

		fm_.show();
	}

	gui::~gui()
	{
	}

	void gui::update()
	{
		dw_.update();
	}

	void gui::prepare_events()
	{
		fm_.events().mouse_move([this](const arg_mouse& args)
		{
			on_mouse_move(args);
		});
		fm_.events().dbl_click([this](const arg_mouse& args)
		{
			on_dbl_click(args);
		});
		fm_.events().mouse_up([this](const arg_mouse& args)
		{
			on_mouse_up(args);
		});
		fm_.events().mouse_down([this](const arg_mouse& args)
		{
			on_mouse_down(args);
		});
		fm_.events().click([this](const arg_mouse& args)
		{
			on_mouse_click(args);
		});
	}

	void gui::draw(paint::graphics& graph)
	{
		buttons_panel_.draw(graph);
		board_panel_.draw(graph);
		drawers::draw(game_, graph);
		animation_player_impl_.draw(graph);
	}

	void gui::on_mouse_move(const arg_mouse& args)
	{
	}

	void gui::on_dbl_click(const arg_mouse& args)
	{
		auto mouse_position = args.pos;
	}

	void gui::on_mouse_up(const nana::arg_mouse& args)
	{
	}

	void gui::on_mouse_click(const nana::arg_mouse& args)
	{
		if (board_panel_.is_hit(args.pos))
		{
			auto hit_field = board_panel_.hit_field(args.pos);
			on_board(hit_field.first, hit_field.second);
		}
		else if (buttons_panel_.is_hit(args.pos))
		{
			size_t hit_button = buttons_panel_.hit_button(args.pos);
			on_button(hit_button);
		}
	}

	void gui::on_mouse_down(const nana::arg_mouse& args)
	{

	}

	void gui::on_board(size_t col, size_t row)
	{
		game_.on_board(col, row);
		update_for_entity();
	}

	void gui::on_button(size_t n)
	{
		game_.on_button(n);
	}

	void gui::prepare_timer()
	{
		timer_.interval(100);
		timer_.elapse(std::bind(&gui::update, this));
		timer_.start();
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
		animation::player<animation::flash_bitmap>::connect([this](animation::flash_bitmap flash_bitmap_data)
		{
			return animation::prepare_animation<animation::flash_bitmap_animation>(animation_player_impl_, flash_bitmap_data);
		});
	}

	void gui::update_for_entity()
	{
		auto selected_index = states::state_controller::selected_index_;
		if (selected_index == -1)
			return;

		auto entity = game_.board_.at(selected_index);
		
		buttons_panel_.set_buttons_for(*entity);
		labels_panel_.set_labels_for(*entity);
	}
};

*/