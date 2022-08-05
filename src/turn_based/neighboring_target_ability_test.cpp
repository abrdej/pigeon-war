#include <turn_based/neighboring_target_ability.h>

#include <turn_based/board.h>

#include <gtest/gtest.h>

#include <boost/range/combine.hpp>

namespace {

struct ability_test : neighboring_target_ability<> {
  ability_test() : neighboring_target_ability<>("ability_test") {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index;
};

}  // namespace

void CompareToExpected(const std::vector<index_t::value_type>& expected_indices) {
  std::set<index_t::value_type> ordered_indices;
  for (const auto& index : game_control().possible_movements_) {
    ordered_indices.insert(index.cast());
  }

  for (const auto& entry : boost::range::combine(ordered_indices, expected_indices)) {
    EXPECT_EQ(boost::get<0>(entry), boost::get<1>(entry));
  }
}

TEST(NeighboringTargetAbility, Prepare) {
  ability_test ability;

  // Board:
  // 0 1 2
  // 3 X 5
  // 6 7 8

  game_board().set_size(3, 3);
  ability.prepare(index_t{4});

  ASSERT_EQ(game_control().possible_movements_.size(), 8u);

  CompareToExpected({0, 1, 2, 3, 5, 6, 7, 8});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{1});
  EXPECT_EQ(ability.selected_index, index_t{1});
}

TEST(NeighboringTargetAbility, PrepareOnBoundary) {
  ability_test ability;

  // Board:
  // 0 1 2
  // X 4 5
  // 6 7 8

  game_board().set_size(3, 3);
  ability.prepare(index_t{3});

  ASSERT_EQ(game_control().possible_movements_.size(), 5u);

  CompareToExpected({0, 1, 4, 6, 7});

  EXPECT_EQ(game_control().actual_targeting_type_, target_types::enemy);
  game_control().do_action(index_t{6});
  EXPECT_EQ(ability.selected_index, index_t{6});
}
