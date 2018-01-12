#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <functional>
#include <typeindex>
#include <chrono>
#include <vector>
#include <client/gui/bitmap_center.h>
#include <client/gui/drawing_manager.h>
#include "common/bitmaps.h"

namespace animation
{
class base_player
{
public:
	static void play()
	{
		starter_();
	}
	static void starter(const std::function<void()>& starter)
	{
		starter_ = starter;
	}
private:
	static std::function<void()> starter_;
};

template <typename Animation>
class player final : public base_player
{
public:
	using function_type = typename std::function<void(Animation)>;

	static void connect(const function_type& fn)
	{
		me_ = std::unique_ptr<player>(new player(fn));
	}

	static void launch(Animation animation)
	{
		me_->_launch(animation);
	}

private:
	static std::unique_ptr<player> me_;
	const function_type fn_;

	explicit player(const function_type& fn)
			: fn_(fn)
	{
	}
	void _launch(Animation animation)
	{
		fn_(animation);
	}
};

template <typename Animation>
std::unique_ptr<player<Animation>> player<Animation>::me_ = nullptr;

struct move
{
	move(sf::Uint64 fi, sf::Uint64 ti, sf::Uint64 id)
			: from_index(fi),
			  to_index(ti),
			  bitmap(drawing_manager::get_bitmap_key_for(id)) {
	}
	move(sf::Uint64 fi, sf::Uint64 ti, bitmap_key bitmap)
			: from_index(fi),
			  to_index(ti),
			  bitmap(bitmap)
	{
	}
	sf::Uint64 from_index;
	sf::Uint64 to_index;
	bitmap_key bitmap;
};

struct move_at_path {
	move_at_path(sf::Uint64 start_index, std::vector<sf::Uint64> path, sf::Uint64 object_id)
			: path(std::move(path)), start_index(start_index), bitmap(drawing_manager::get_bitmap_key_for(object_id)) {
	}
	move_at_path(sf::Uint64 start_index, std::vector<sf::Uint64> path, bitmap_key bitmap)
			: path(std::move(path)), start_index(start_index), bitmap(bitmap) {}
	std::vector<sf::Uint64> path;
	bitmap_key bitmap;
	sf::Uint64 start_index;
};

struct move_entity
{
	move_entity(sf::Uint64 from_index, sf::Uint64 to_index, sf::Uint64 entity_id)
			: from_index(from_index),
			  to_index(to_index),
			  entity_id(entity_id)
	{
	}
	sf::Uint64 from_index;
	sf::Uint64 to_index;
	sf::Uint64 entity_id;
};

struct bum
{
	bum(sf::Uint64 on_index)
			: on_index(on_index)
	{
	}
	sf::Uint64 on_index;
};

struct claws
{
	claws(sf::Uint64 on_index)
			: on_index(on_index)
	{
	}
	sf::Uint64 on_index;
};

struct flash_bitmap
{
	flash_bitmap(sf::Uint64 on_index, std::chrono::milliseconds duration, const std::string& bitmap_name)
			: on_index(on_index),
			  duration(duration),
			  bitmap_name(bitmap_name)
	{
	}
	flash_bitmap(sf::Uint64 on_index, std::chrono::milliseconds duration, const bitmap_key& bmt_key)
			: on_index(on_index),
			  duration(duration),
			  bmt_key(bmt_key)
	{
	}
	sf::Uint64 on_index;
	std::chrono::milliseconds duration;
	std::string bitmap_name;
	bitmap_key bmt_key;
};

struct change_health
{
	change_health(sf::Uint64 for_index, sf::Int32 change_by)
			: for_index(for_index),
			  change_by(change_by)
	{
	}
	sf::Uint64 for_index;
	sf::Int32 change_by;
};
};

#endif