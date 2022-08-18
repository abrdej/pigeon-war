#include <turn_based/neighboring_target_ability.h>

#include <gtest/gtest.h>

#include <turn_based/board.h>
#include <turn_based/testing/compare.h>

namespace {

struct ability_test : neighboring_target_ability<> {
  explicit ability_test(bool available = true)
      : neighboring_target_ability<>("ability_test", target_types::enemy, available) {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index;
};

}  // namespace

TEST(NeighboringTargetAbility, Prepare) {
  ability_test ability;

  // Board:
  // 0 1 E
  // 3 X 5
  // E 7 8

  game_board() = board();
  game_board().set_size(3, 3);
  game_board().insert(index_t{2}, entity_id_t{1});
  game_board().insert(index_t{6}, entity_id_t{2});

  ability.prepare(index_t{4});

  ASSERT_EQ(game_control().possible_movements.size(), 6u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {0, 1, 3, 5, 7, 8});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{1});
  EXPECT_EQ(ability.selected_index, index_t{1});
}

TEST(NeighboringTargetAbility, PrepareOnBoundary) {
  ability_test ability;

  // Board:
  // 0 1 2
  // X 4 5
  // 6 7 8

  game_board() = board();
  game_board().set_size(3, 3);
  ability.prepare(index_t{3});

  ASSERT_EQ(game_control().possible_movements.size(), 5u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {0, 1, 4, 6, 7});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{6});
  EXPECT_EQ(ability.selected_index, index_t{6});
}

TEST(NeighboringTargetAbility, PrepareIncludingOccupied) {
  ability_test ability(false);

  // Board:
  // 0 1 E
  // 3 X 5
  // E 7 8

  game_board() = board();
  game_board().set_size(3, 3);
  game_board().insert(index_t{2}, entity_id_t{1});
  game_board().insert(index_t{6}, entity_id_t{2});

  ability.prepare(index_t{4});

  ASSERT_EQ(game_control().possible_movements.size(), 8u);

  testing::CompareWithoutOrdering(game_control().possible_movements, {0, 1, 2, 3, 5, 6, 7, 8});

  EXPECT_EQ(game_control().current_targeting_type, target_types::enemy);
  game_control().do_action(index_t{1});
  EXPECT_EQ(ability.selected_index, index_t{1});
}
