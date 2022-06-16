#include <core/game.h>
#include <entities/entities_factory.h>
#include <managers/entity_manager.h>

int main(int argc, char** argv) {
  entities_factory factory;
  auto shooter_id = factory.create("shooter");
  auto saberhand_id = factory.create("saberhand");
  auto saurian_id = factory.create("saurian");
  auto saurian_web_id = factory.create("saurian_web");

  (void)shooter_id;
  (void)saberhand_id;
  (void)saurian_id;
  (void)saurian_web_id;

  game::get<entity_manager>().clear();

  return 0;
}
