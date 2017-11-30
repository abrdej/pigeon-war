#include "gui/gui.h"

int main() {

	view::bitmap_center::load();

	game game;
	view::gui g(game);
	g.run();

	return 0;
};