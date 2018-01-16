#include "pigeon_war_client.h"

std::int32_t main() {

	view::bitmap_center::load();

	view::pigeon_war_client client;
	client.run();

	return 0;
};