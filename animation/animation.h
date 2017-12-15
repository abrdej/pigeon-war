#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <functional>
#include <typeindex>
#include <chrono>
#include <vector>

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
	move(size_t fi, size_t ti, std::size_t id)
			: from_index(fi),
			  to_index(ti),
			  object_id(id)
	{
	}
	size_t from_index;
	size_t to_index;
	std::size_t object_id;
};

struct move_at_path {
	move_at_path(std::size_t start_index, std::vector<std::size_t> path, std::size_t object_id)
			: path(std::move(path)), start_index(start_index), object_id(object_id) {}
	std::vector<std::size_t> path;
	std::size_t object_id;
	std::size_t start_index;
};

struct move_entity
{
	move_entity(size_t from_index, size_t to_index, size_t entity_id)
			: from_index(from_index),
			  to_index(to_index),
			  entity_id(entity_id)
	{
	}
	size_t from_index;
	size_t to_index;
	size_t entity_id;
};

struct bum
{
	bum(size_t on_index)
			: on_index(on_index)
	{
	}
	size_t on_index;
};

struct claws
{
	claws(size_t on_index)
			: on_index(on_index)
	{
	}
	size_t on_index;
};

struct flash_bitmap
{
	flash_bitmap(size_t on_index, std::chrono::milliseconds duration, const std::string& bitmap_name)
			: on_index(on_index),
			  duration(duration),
			  bitmap_name(bitmap_name)
	{
	}
	size_t on_index;
	std::chrono::milliseconds duration;
	std::string bitmap_name;
};

struct change_health
{
	change_health(size_t for_index, int change_by)
			: for_index(for_index),
			  change_by(change_by)
	{
	}
	size_t for_index;
	int change_by;
};
};

#endif