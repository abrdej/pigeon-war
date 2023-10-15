#include <json.hpp>

#include <networking/client.h>
#include <networking/socket_connection.h>

volatile std::sig_atomic_t processing_interrupted = false;

extern "C" void interrupt_processing( int ) {
  processing_interrupted = true;
}

std::string create_game_for_single_player() {
  nlohmann::json game_request;
  game_request["scenario"] = "saurian_web";
  game_request["map"] = "saurian_web";
  game_request["number_of_players"] = 1;
  game_request["game_hash"] = "";

  nlohmann::json message;
  message["game_request"] = game_request;

  return message.dump();
}

std::string find_opponent_and_create_game() {
  nlohmann::json game_request;
  game_request["scenario"] = "saurian_web";
  game_request["map"] = "saurian_web";
  game_request["number_of_players"] = 2;
  game_request["game_hash"] = "";

  nlohmann::json message;
  message["game_request"] = game_request;

  return message.dump();
}

std::string make_incorrect_create_game_message() {
  nlohmann::json game_request;
  game_request["scenario"] = "saurian_web";
  game_request["map"] = "saurian_web";

  nlohmann::json message;
  message["game_request"] = game_request;

  return message.dump();
}

std::string make_message(const std::string& text) {
  nlohmann::json message;
  message["message"] = text;
  return message.dump();
}

int main(int argc, char** argv) {
  using namespace networking;
  client client;

  client.connect("127.0.0.1", 60000);

  client.on_message([&client](const std::string& message) {
    std::cout << "Got message from server: " << message << "\n";
    client.send("Hello my game, this message should be forwarded to you");
  });


  // What we want to test
  // - creating a game
  // - joining a game
  // - finding opponent and joining a game
  // - when all client disconnect, game should be removed
  // - when client disconnect for a while, it should be re-added to the game

  client.send(make_incorrect_create_game_message());

  while (!processing_interrupted) {
    client.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  // TODO: close client?

  std::cout << "Client finished\n";
}
