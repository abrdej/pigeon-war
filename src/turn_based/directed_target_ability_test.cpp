#include <turn_based/directed_target_ability.h>

#include <gtest/gtest.h>

#include <turn_based/board.h>
#include <turn_based/testing/compare.h>

namespace {

struct ability_test : directed_target_ability<> {
  explicit ability_test(bool skip_obstacles = false)
      : directed_target_ability<>("ability_test", 2, target_types::enemy, skip_obstacles) {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index;
};

}  // namespace

TEST(DirectedTargetAbility, Prepare) {
  ability_test ability;

  // Board:
  // 0  1  2  3  4
  // 5  E  E  8  9
  // 10 11 X  13 14
  // 15 16 17 18 19
  // 20 21 22  23 E

  game_board() = board();
  game_board().set_size(5, 5);
  game_board().insert(index_t{6}, entity_id_t{1});
  game_board().insert(index_t{7}, entity_id_t{2});
  game_board().insert(index_t{24}, entity_id_t{3});

  ability.prepare(index_t{12});

  ASSERT_EQ(game_control().possible_movements_.size(), 14u);

  testing::CompareWithoutOrdering(game_control().possible_movements_,
                                  {4, 6, 7, 8, 10, 11, 13, 14, 16, 17, 18, 20, 22, 24});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{6});
  EXPECT_EQ(ability.selected_index, index_t{6});
}

TEST(DirectedTargetAbility, PrepareOnBoundaryTL) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 11u);

  testing::CompareWithoutOrdering(game_control().possible_movements_,
                                  {0, 1, 2, 5, 7, 8, 10, 11, 12, 16, 18});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{12});
  EXPECT_EQ(ability.selected_index, index_t{12});
}

TEST(DirectedTargetAbility, PrepareOnBoundaryBR) {
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

  ASSERT_EQ(game_control().possible_movements_.size(), 11u);

  testing::CompareWithoutOrdering(game_control().possible_movements_,
                                  {6, 8, 12, 13, 14, 16, 17, 19, 22, 23, 24});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{6});
  EXPECT_EQ(ability.selected_index, index_t{6});
}

TEST(DirectedTargetAbility, PrepareSkipObstacles) {
  ability_test ability(true);

  // Board:
  // 0  1  2  3  4
  // 5  E  E  8  9
  // 10 11 X  13 14
  // 15 16 17 18 19
  // 20 21 22 23 E

  game_board() = board();
  game_board().set_size(5, 5);
  game_board().insert(index_t{6}, entity_id_t{1});
  game_board().insert(index_t{7}, entity_id_t{2});
  game_board().insert(index_t{24}, entity_id_t{3});

  ability.prepare(index_t{12});

  ASSERT_EQ(game_control().possible_movements_.size(), 16u);

  testing::CompareWithoutOrdering(game_control().possible_movements_,
                                  {0, 2, 4, 6, 7, 8, 10, 11, 13, 14, 16, 17, 18, 20, 22, 24});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{4});
  EXPECT_EQ(ability.selected_index, index_t{4});
}
