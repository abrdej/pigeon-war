#include "pigeon_war_client.h"

std::int32_t main(int argc, char** argv) {

	view::bitmap_center::load();

//	std::string address = "127.0.0.1";
	std::string address = "80.211.186.19";

//	int port = 5555;
	int port = 443;

	if (argc > 1) {
		address = argv[1];
		port = std::atoi(argv[2]);
	}

	view::pigeon_war_client client(address, port);
	client.run();

	return 0;
};