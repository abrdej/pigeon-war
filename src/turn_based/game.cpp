#include <turn_based/game.h>

game& game::get_game() {
  static game game_instance;
  return game_instance;
}
