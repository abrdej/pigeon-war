#include <entities/entities_factory.h>

int main(int argc, char** argv) {

  auto n = entities_factory::create("shooter");
  (void)n;

  return 0;
}
