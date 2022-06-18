#include <turn_based/game.h>
#include <turn_based/entities_factory.h>
#include <turn_based/managers/entity_manager.h>

int main(int argc, char** argv) {
  game::get<entities_factory>();

  auto shooter_id = game::get<entities_factory>().create("shooter");
  auto saberhand_id = game::get<entities_factory>().create("saberhand");
  auto saurian_id = game::get<entities_factory>().create("saurian");
  auto saurian_web_id = game::get<entities_factory>().create("saurian_web");
  auto native_id = game::get<entities_factory>().create("native");

  (void)shooter_id;
  (void)saberhand_id;
  (void)saurian_id;
  (void)saurian_web_id;
  (void)native_id;

//  game::get<entity_manager>().clear();

  return 0;
}
