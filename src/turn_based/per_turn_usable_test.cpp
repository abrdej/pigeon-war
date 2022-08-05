#include <turn_based/per_turn_usable.h>

#include <gtest/gtest.h>

struct per_turn_usable_tester : per_turn_usable {
  [[nodiscard]] bool Usable() const {
    return !used;
  }

  void Use() {
    used = true;
  }
};

TEST(PerTurnUsable, ResetUsed) {
  per_turn_usable_tester tester;
  EXPECT_TRUE(tester.Usable());
  for (std::int32_t i = 0; i < 3; ++i) {
    tester.Use();
    EXPECT_FALSE(tester.Usable());
    game::get<turn_system>().end_turn();
    EXPECT_FALSE(tester.Usable());
    game::get<turn_system>().end_turn();
    EXPECT_TRUE(tester.Usable());
  }
}
