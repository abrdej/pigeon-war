#include <turn_based/straight_target_ability.h>

#include <gtest/gtest.h>

#include <turn_based/board.h>
#include <turn_based/testing/compare.h>

namespace {

struct ability_test : straight_target_ability<> {
  explicit ability_test(bool skip_obstacles = false)
      : straight_target_ability<>("ability_test", 2, target_types::enemy, skip_obstacles) {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index;
};

}  // namespace

TEST(StraightTargetAbility, Prepare) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 7u);

  testing::CompareWithoutOrdering(game_control().possible_movements_, {2, 7, 11, 13, 14, 17, 22});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{2});
  EXPECT_EQ(ability.selected_index, index_t{2});
}

TEST(StraightTargetAbility, PrepareOnBoundaryTL) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 6u);

  testing::CompareWithoutOrdering(game_control().possible_movements_, {1, 5, 7, 8, 11, 16});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{11});
  EXPECT_EQ(ability.selected_index, index_t{11});
}

TEST(StraightTargetAbility, PrepareOnBoundaryBR) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 6u);

  testing::CompareWithoutOrdering(game_control().possible_movements_, {8, 13, 16, 17, 19, 23});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{8});
  EXPECT_EQ(ability.selected_index, index_t{8});
}

TEST(StraightTargetAbility, PrepareSkipObstacles) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 8u);

  testing::CompareWithoutOrdering(game_control().possible_movements_, {2, 7, 10, 11, 13, 14, 17, 22});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{2});
  EXPECT_EQ(ability.selected_index, index_t{2});
}
