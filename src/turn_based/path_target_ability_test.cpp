#include <turn_based/path_target_ability.h>

#include <gtest/gtest.h>

#include <turn_based/board.h>
#include <turn_based/testing/compare.h>

namespace {

struct ability_test : path_target_ability {
  explicit ability_test(bool all_fields = false)
      : path_target_ability("ability_test", 2, target_types::enemy, all_fields) {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index;
};

}  // namespace

TEST(PathTargetAbility, Prepare) {
  ability_test ability;

  // Board:
  // 0  1  2  3  4
  // 5  6  7  8  9
  // 10 E  X  13 14
  // 15 16 17 18 19
  // 20 21 E  23 24

  game_board() = board();
  game_board().set_size(5, 5);
  game_board().insert(index_t{11}, entity_id_t{1});
  game_board().insert(index_t{22}, entity_id_t{2});

  ability.prepare(index_t{12});

  ASSERT_EQ(game_control().possible_movements.size(), 9u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {2, 6, 7, 8, 13, 14, 16, 17, 18});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{2});
  EXPECT_EQ(ability.selected_index, index_t{2});
}

TEST(PathTargetAbility, PrepareOnBoundaryTL) {
  ability_test ability;

  // Board:
  // 0  1  2  3  4
  // 5  X  7  8  9
  // 10 11 12 13 14
  // 15 16 17 18 19
  // 20 21 22 23 24

  game_board() = board();
  game_board().set_size(5, 5);

  ability.prepare(index_t{6});

  ASSERT_EQ(game_control().possible_movements.size(), 10u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {0, 1, 2, 5, 7, 8, 10, 11, 12, 16});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{11});
  EXPECT_EQ(ability.selected_index, index_t{11});
}

TEST(PathTargetAbility, PrepareOnBoundaryBR) {
  ability_test ability;

  // Board:
  // 0  1  2  3  4
  // 5  6  7  8  9
  // 10 11 12 13 14
  // 15 16 17 X  19
  // 20 21 22 23 24

  game_board() = board();
  game_board().set_size(5, 5);

  ability.prepare(index_t{18});

  ASSERT_EQ(game_control().possible_movements.size(), 10u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {8, 12, 13, 14, 16, 17, 19, 22, 23, 24});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{8});
  EXPECT_EQ(ability.selected_index, index_t{8});
}

TEST(PathTargetAbility, AllFields) {
  ability_test ability(true);

  // Board:
  // 0  1  2  3  4
  // 5  6  7  8  9
  // 10 E  X  13 14
  // 15 16 17 18 19
  // 20 21 E  23 24

  game_board() = board();
  game_board().set_size(5, 5);
  game_board().insert(index_t{11}, entity_id_t{1});
  game_board().insert(index_t{22}, entity_id_t{2});

  ability.prepare(index_t{12});

  ASSERT_EQ(game_control().possible_movements.size(), 12u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {2, 6, 7, 8, 10, 11, 13, 14, 16, 17, 18, 22});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{2});
  EXPECT_EQ(ability.selected_index, index_t{2});
}
