#include "client/gui/pigeon_war_client.h"

int main() {

	view::bitmap_center::load();

	view::pigeon_war_client client;
	client.run();

	return 0;
};