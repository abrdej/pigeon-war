#include <networking/client.h>
#include <networking/socket_connection.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

int main(int argc, char** argv) {
  using namespace networking;
  client client;

  client.connect("127.0.0.1", 6000);

  client.on_message([](const std::string& message) {
    std::cout << "Got message from server: " << message << "\n";
  });

  client.send("Hello my server\n");

  while (!processing_interrupted) {
    client.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  // TODO: close client?

  std::cout << "Client finished\n";
}
