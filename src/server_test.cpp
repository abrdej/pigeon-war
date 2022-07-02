#include <networking/server.h>
#include <networking/socket_connection.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
  using namespace networking;
  server<socket_connection> server(6000);

  server.on_client_accepted([&](std::shared_ptr<networking::socket_connection> client) {
    std::cout << "Client accepted: " << client->get_id() << "\n";
    server.send_message_to_all("Hello my client\n");
  });

  server.on_message([](std::uint32_t client_id, const std::string& message) {
    std::cout << "Got message from client: " << client_id << ", which is: " << message << "\n";
  });

  server.start();
  while (!processing_interrupted) {
    server.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  server.stop();

  std::cout << "Server finished\n";
}