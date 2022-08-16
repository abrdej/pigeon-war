#include <turn_based/caster_target_ability.h>

#include <turn_based/board.h>

#include <gtest/gtest.h>

namespace {

struct ability_test : caster_target_ability {
  ability_test() : caster_target_ability("ability_test") {}

  void use(index_t use_on_index) override {
    selected_index = use_on_index;
  }

  index_t selected_index{std::numeric_limits<index_t::value_type>::max()};
};

}  // namespace

TEST(CasterTargetAbility, Prepare) {
  ability_test ability{};

  game_board() = board();
  game_board().set_size(3, 3);

  // add some values that are expected to be overwritten
  game_control().possible_movements_ = {index_t{0}, index_t{5}};

  ability.prepare(index_t{4});

  ASSERT_EQ(game_control().possible_movements_.size(), 1u);
  EXPECT_EQ(game_control().possible_movements_.front(), index_t{4});
  EXPECT_EQ(game_control().actual_targeting_type_, target_types::caster);

  game_control().do_action(index_t{4});

  EXPECT_EQ(ability.selected_index, index_t{4});
}
