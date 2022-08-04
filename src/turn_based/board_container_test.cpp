#include <turn_based/board_container.h>

#include <gtest/gtest.h>

using namespace turn_based;

using board_container_type = board_container<std::int32_t, std::numeric_limits<std::int32_t>::max()>;

TEST(BoardContainer, General) {
  board_container_type board(10, 8);
  EXPECT_EQ(board.rows(), 8);
  EXPECT_EQ(board.cols(), 10);
  EXPECT_TRUE(board.empty_at(10));
  board.insert(10, 5);
  EXPECT_FALSE(board.empty_at(10));
  board.move(10, 13);
  EXPECT_TRUE(board.empty_at(10));
  EXPECT_FALSE(board.empty_at(13));
  EXPECT_EQ(board.at(13), 5);
  auto entity_id = board.take(13);
  ASSERT_EQ(entity_id, 5);
  EXPECT_TRUE(board.empty_at(13));
  board.insert(15, entity_id);
  EXPECT_FALSE(board.empty_at(15));
  board.remove(15);
  EXPECT_TRUE(board.empty_at(15));
}

TEST(BoardContainer, Multi) {
  board_container_type board(10, 8);
  board.insert(10, 5);
  board.insert(10, 6);
  board.remove(10);
  EXPECT_FALSE(board.empty_at(10));
  board.remove(10);
  EXPECT_TRUE(board.empty_at(10));
  board.insert(7, 3);
  board.insert(7, 4);
  EXPECT_EQ(board.take_bottom(7), 3);
  board.insert_bottom(7, 2);
  EXPECT_EQ(board.take_bottom(7), 2);
  board.insert(7, 5);
  board.remove_bottom(7);
  EXPECT_EQ(board.at(7), 5);
  EXPECT_EQ(board.each_at(7).size(), 1);
  board.insert(15, 5);
  board.insert(15, 6);
  board.insert(15, 7);
  EXPECT_EQ(board.each_at(15).size(), 3);
  board.remove_each(15);
  EXPECT_EQ(board.each_at(15).size(), 0);
  EXPECT_TRUE(board.empty_at(15));
}

TEST(BoardContainer, MoveEach) {
  board_container_type board(10, 8);
  board.insert(11, 2);
  board.insert(11, 3);
  board.insert(11, 4);
  board.move_each(11, 13);
  ASSERT_EQ(board.each_at(13).size(), 3);
  EXPECT_EQ(board.each_at(13)[0], 2);
  EXPECT_EQ(board.each_at(13)[1], 3);
  EXPECT_EQ(board.each_at(13)[2], 4);
}

TEST(BoardContainer,TakeEach) {
  board_container_type board(10, 8);
  board.insert(11, 2);
  board.insert(11, 3);
  board.insert(11, 4);
  auto taken = board.take_each(11);
  EXPECT_TRUE(board.empty_at(11));
  ASSERT_EQ(taken.size(), 3);
  EXPECT_EQ(taken[0], 2);
  EXPECT_EQ(taken[1], 3);
  EXPECT_EQ(taken[2], 4);
}

TEST(BoardContainer, IndexFor) {
  board_container_type board(10, 8);
  board.insert(11, 5);
  board.insert(5, 2);
  board.insert(9, 3);
  EXPECT_EQ(board.index_for(5), 11);
}

TEST(BoardContainer, RemoveEntity) {
  board_container_type board(10, 8);
  board.insert(11, 4);
  board.insert(11, 5);
  board.insert(11, 6);
  board.remove_entity(5);
  auto remaining = board.each_at(11);
  EXPECT_EQ(remaining[0], 4);
  EXPECT_EQ(remaining[1], 6);
}

TEST(BoardContainer, ForEach) {
  board_container_type board(10, 8);
  board.insert(11, 4);
  board.insert(11, 5);
  board.insert(12, 6);
  board.insert(13, 7);
  std::vector<board_container_type::value_type> visited_ids;
  board.for_each([&visited_ids](
      board_container_type::value_type id, board_container_type::index_type x, board_container_type::index_type y) {
    if (id != board_container_type::empty_value) {
      visited_ids.push_back(id);
    }
  });
  ASSERT_EQ(visited_ids.size(), 4);
  EXPECT_EQ(visited_ids[0], 4);
  EXPECT_EQ(visited_ids[1], 5);
  EXPECT_EQ(visited_ids[2], 6);
  EXPECT_EQ(visited_ids[3], 7);
}
