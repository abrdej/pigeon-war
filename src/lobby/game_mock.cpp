#include <networking/server.h>
#include <networking/socket_connection.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
  std::int32_t port = 0;
  if (argc > 1) {
    port = std::atoi(argv[1]);
  }

  using namespace networking;
  server<socket_connection> server(port);

  LOG(debug) << "Loading game mock server on port: " << port;

  server.on_client_accepted([&](std::shared_ptr<socket_connection> client) {
    const auto client_id = client->get_id();
    LOG(debug) << "new client accepted with id: " << client_id;
    LOG(debug) << "Sending initial messages to client";
    server.send_message(client_id, "Hello client, I'm a server mock");
  });

  server.on_message([&](std::uint32_t client_id, const std::string& message) {
    LOG(debug) << "got new message: " << message << ", from client: " << client_id;
  });

  server.start();
  while (!processing_interrupted) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  server.stop();

  LOG(debug) << "server finishing.";
}
