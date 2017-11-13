#include "animations_objects.h"
#include "gui/board_panel.h"
#include "gui/bitmap_center.h"
#include "utils/utility.h"
#include "abilities/shoot.h"
#include "gui/drawer.h"

namespace animation
{
	move_object_animation::move_object_animation(move move_data)
		: index_from_(move_data.from_index),
		index_to_(move_data.to_index),
		object_type_(move_data.object_type),
		bitmap_(view::bitmap_center::get_image_for_entity(move_data.object_type))
	{
		double time_step = 1.;
		velocity_ = 20.;

		start_pos_ = static_cast<sf::Vector2f>(view::board_index_to_point(index_from_));
		actual_pos_ = start_pos_;
		end_pos_ = static_cast<sf::Vector2f>(view::board_index_to_point(index_to_));

		double alpha = std::atan2(end_pos_.y - start_pos_.y, end_pos_.x - start_pos_.x);
		double distance_step = time_step * velocity_;

		double x_step = std::cos(alpha) * distance_step;
		double y_step = std::sin(alpha) * distance_step;

		translation_ = sf::Vector2f(x_step, y_step);
		turn_ = translation_.x < 0 ? turn_types::left : turn_types::right;
	}

	void move_object_animation::draw(sf::RenderWindow& window)
	{
		sf::Sprite sprite;
		sprite.setPosition(actual_pos_);
		sprite.setTexture(bitmap_);
		sprite.setTextureRect(turn_ == turn_types::left ? sf::IntRect(60, 0, -60, 60) : sf::IntRect(0, 0, 60, 60));
		window.draw(sprite);
	}

	bool move_object_animation::run()
	{
		actual_pos_ += translation_;
		if (util::distance(actual_pos_, end_pos_) < 10)
			return true;
		return false;
	}

	move_object_animation2::move_object_animation2(move_entity move_data)
		: index_from_(move_data.from_index),
		index_to_(move_data.to_index),
		entity_id_(move_data.entity_id)
		//bitmap_(view::bitmap_center::get_image_for_entity(move_data.object_type))
		//sprite_(view::board_drawer::draw_data_[move_data.entity_id].sprite_)
	{
		double time_step = 1.;
		velocity_ = 20.;

		start_pos_ = static_cast<sf::Vector2f>(view::board_index_to_point(index_from_));
		actual_pos_ = start_pos_;
		end_pos_ = static_cast<sf::Vector2f>(view::board_index_to_point(index_to_));

		double alpha = std::atan2(end_pos_.y - start_pos_.y, end_pos_.x - start_pos_.x);
		double distance_step = time_step * velocity_;

		double x_step = std::cos(alpha) * distance_step;
		double y_step = std::sin(alpha) * distance_step;

		translation_ = sf::Vector2f(x_step, y_step);
		turn_ = translation_.x < 0 ? turn_types::left : turn_types::right;
	}

	void move_object_animation2::draw(sf::RenderWindow& window)
	{
		//sprite_.setPosition(actual_pos_);
		//sprite_.setTextureRect(turn_ == turn_types::left ? sf::IntRect(60, 0, -60, 60) : sf::IntRect(0, 0, 60, 60));
		//window.draw(sprite_);
	}

	bool move_object_animation2::run()
	{
		actual_pos_ += translation_;
		if (util::distance(actual_pos_, end_pos_) < 10)
			return true;
		return false;
	}


	flash_bitmap_animation::flash_bitmap_animation(flash_bitmap flash_bitmap_data)
		: on_point_(view::board_index_to_point(flash_bitmap_data.on_index)),
		start_time_(std::chrono::system_clock::now()),
		duration_(flash_bitmap_data.duration)
	{
		bitmap_.loadFromFile(flash_bitmap_data.bitmap_name);
	}

	void flash_bitmap_animation::draw(sf::RenderWindow& window)
	{
		sf::Sprite sprite;
		sprite.setPosition(on_point_);
		sprite.setTexture(bitmap_);
		window.draw(sprite);
	}

	bool flash_bitmap_animation::run()
	{
		using namespace std::chrono;
		auto now_time = system_clock::now();
		auto ellapsed = duration_cast<milliseconds>(now_time - start_time_);
		if (ellapsed >= duration_)
			return true;
		return false;
	}

	change_health_animation::change_health_animation(change_health change_health_data)
		: point_(view::board_index_to_point(change_health_data.for_index)),
		start_time_(std::chrono::system_clock::now()),
		change_by_(change_health_data.change_by),
		duration_(std::chrono::milliseconds(300))
	{
		font_.loadFromFile("verdanab.ttf");

		point_.x += view::constants::field_size / 4.;
		point_.y -= view::constants::field_size / 3.;
	}

	void change_health_animation::draw(sf::RenderWindow& window)
	{
		sf::Text text;
		text.setFont(font_);
		text.setColor(sf::Color(210, 20, 15));
		text.setPosition(point_);
		text.setString(std::to_string(change_by_));
		window.draw(text);
	}

	bool change_health_animation::run()
	{
		using namespace std::chrono;
		auto now_time = system_clock::now();
		auto ellapsed = duration_cast<milliseconds>(now_time - start_time_);

		point_.y -= view::constants::field_size / 8.;

		if (ellapsed >= duration_)
			return true;
		return false;
	}
};

/*

namespace animation
{
	move_object_animation::move_object_animation(move move_data)
		: index_from_(move_data.from_index),
		index_to_(move_data.to_index),
		object_type_(move_data.object_type)
	{
		double time_step = 1.;
		velocity_ = 20.;

		start_pos_ = view::board_index_to_point(index_from_);
		actual_pos_ = start_pos_;
		end_pos_ = view::board_index_to_point(index_to_);

		double alpha = std::atan2(end_pos_.y - start_pos_.y, end_pos_.x - start_pos_.x);
		double distance_step = time_step * velocity_;

		double x_step = std::cos(alpha) * distance_step;
		double y_step = std::sin(alpha) * distance_step;

		translation_ = nana::point(x_step, y_step);
	}

	void move_object_animation::draw(nana::paint::graphics& graph)
	{
		auto bitmap = view::bitmap_center::get_image_for_entity(object_type_);
		bitmap.paste(graph, actual_pos_.x, actual_pos_.y);
	}

	bool move_object_animation::run()
	{
		actual_pos_ += translation_;
		if (util::distance(actual_pos_, end_pos_) < 10)
			return true;
		return false;
	}

	flash_bitmap_animation::flash_bitmap_animation(flash_bitmap flash_bitmap_data)
		: on_point_(view::board_index_to_point(flash_bitmap_data.on_index)),
		start_time_(std::chrono::system_clock::now()),
		duration_(flash_bitmap_data.duration),
		bitmap_(nana::paint::image(flash_bitmap_data.bitmap_name))
	{
	}

	void flash_bitmap_animation::draw(nana::paint::graphics& graph)
	{
		bitmap_.paste(graph, on_point_.x, on_point_.y);
	}

	bool flash_bitmap_animation::run()
	{
		using namespace std::chrono;
		auto now_time = system_clock::now();
		auto ellapsed = duration_cast<milliseconds>(now_time - start_time_);
		if (ellapsed >= duration_)
			return true;
		return false;
	}
};*/