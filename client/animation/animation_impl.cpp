#include "animation_impl.h"
#include <thread>
#include <chrono>
#include "client/gui/bitmap_center.h"
#include "client/gui/board_panel.h"
#include <thread>
#include "utils/utility.h"
#include "animation.h"

namespace animation
{
player_impl::player_impl(const std::function<void()>& updater)
		: updater_(updater)
{
}

void player_impl::run()
{
	while (true)
	{
		if (run_frame())
			break;

		updater_();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	drawers_.clear();
	runners_.clear();
}
};