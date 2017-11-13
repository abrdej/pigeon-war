#ifndef ANIMATION_IMPL_H
#define ANIMATION_IMPL_H

#include "animation.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <algorithm>

namespace animation
{
	class player_impl final
	{
	public:
		player_impl() = default;
		explicit player_impl(const std::function<void()>& updater);
		void updater(const std::function<void()>& updater)
		{
			updater_ = updater;
		}

		typedef std::function<void(sf::RenderWindow&)> drawer_function_type;
		typedef std::function<bool()> runner_function_type;
		typedef std::shared_ptr<drawer_function_type> drawer_type;
		typedef std::shared_ptr<runner_function_type> runner_type;

		void run();
		void draw(sf::RenderWindow& window)
		{
			for (auto& drawer : drawers_)
				(*drawer)(window);
		}
		template <typename T>
		void animations(const std::shared_ptr<T>& animation_ptr)
		{
			add_drawer(drawer(animation_ptr));
			add_runner(runner(animation_ptr));
		}
	private:
		bool run_frame()
		{
			bool result = true;
			for (auto& runner : runners_)
				result = (result && (*runner)());
			return result;
		}
		void add_drawer(const drawer_type& drawer)
		{
			drawers_.push_back(drawer);
		}
		void add_runner(const runner_type& runner)
		{
			runners_.push_back(runner);
		}

	private:
		std::function<void()> updater_;
		std::vector<drawer_type> drawers_;
		std::vector<runner_type> runners_;
	};

	template <typename T>
	typename player_impl::drawer_type drawer(const std::shared_ptr<T>& animation_object)
	{
		return std::make_shared<typename player_impl::drawer_function_type>([animation_object](sf::RenderWindow& window)
		{
			return animation_object->draw(window);
		});
	}

	template <typename T>
	typename player_impl::runner_type runner(const std::shared_ptr<T>& animation_object)
	{
		return std::make_shared<typename player_impl::runner_function_type>([animation_object]()
		{
			return animation_object->run();
		});
	}

	template <typename Animation, typename AnimationData>
	void prepare_animation(player_impl& player_impl, AnimationData data)
	{
		auto animation_ptr = std::make_shared<Animation>(data);
		player_impl.animations(animation_ptr);
		//player_impl.run();
	}
};


/*#include "board.h"
#include "animation.h"
#include <nana\gui.hpp>
#include <thread>
#include <algorithm>

namespace animation
{
	class player_impl final
	{
	public:
		player_impl(){}
		player_impl(const std::function<void()>& updater);
		void updater(const std::function<void()>& updater)
		{
			updater_ = updater;
		}

		typedef std::function<void(nana::paint::graphics& graph)> drawer_function_type;
		typedef std::function<bool()> runner_function_type;
		typedef std::shared_ptr<drawer_function_type> drawer_type;
		typedef std::shared_ptr<runner_function_type> runner_type;

		void run();
		void draw(nana::paint::graphics& graph)
		{
			for (auto& drawer : drawers_)
				(*drawer)(graph);
		}
		template <typename T>
		void animations(const std::shared_ptr<T>& animation_ptr)
		{
			add_drawer(drawer(animation_ptr));
			add_runner(runner(animation_ptr));
		}
	private:
		bool run_frame()
		{
			bool result = true;
			for (auto& runner : runners_)
				result = (result && (*runner)());
			return result;
		}
		void add_drawer(const drawer_type& drawer)
		{
			drawers_.push_back(drawer);
		}
		void add_runner(const runner_type& runner)
		{
			runners_.push_back(runner);
		}
		
	private:
		std::function<void()> updater_;
		std::vector<drawer_type> drawers_;
		std::vector<runner_type> runners_;
	};

	template <typename T>
	typename player_impl::drawer_type drawer(const std::shared_ptr<T>& animation_object)
	{
		return std::make_shared<typename player_impl::drawer_function_type>([animation_object](nana::paint::graphics& graph)
		{
			return animation_object->draw(graph);
		});
	}

	template <typename T>
	typename player_impl::runner_type runner(const std::shared_ptr<T>& animation_object)
	{
		return std::make_shared<typename player_impl::runner_function_type>([animation_object]()
		{
			return animation_object->run();
		});
	}

	template <typename Animation, typename AnimationData>
	void prepare_animation(player_impl& player_impl, AnimationData data)
	{
		auto animation_ptr = std::make_shared<Animation>(data);
		player_impl.animations(animation_ptr);
		//player_impl.run();
	}
};
*/
#endif