#include "pigeon_war_client.h"

sf::Int32 main() {

	view::bitmap_center::load();

	view::pigeon_war_client client;
	client.run();

	return 0;
};