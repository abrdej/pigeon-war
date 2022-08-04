#include <turn_based/turn_system.h>

#include <gtest/gtest.h>

TEST(TurnSystem, SetCallbackEveryTurn) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_turn, 0, [&counter]() {
    ++counter;
  });
  for (std::int32_t i = 1; i <= 5; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i);
  }
}

TEST(TurnSystem, SetCallbackEveryTwoTurnFromThis) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_two_turns_from_this, 0, [&counter]() {
    ++counter;
  });
  std::int32_t j = 0;
  for (std::int32_t i = 1; i <= 5; ++i) {
    turns.end_turn();
    if (i % 2 != 0) {
      ++j;
    }
    EXPECT_EQ(counter, j);
  }
}

TEST(TurnSystem, SetCallbackEveryTwoTurnFromNext) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_two_turns_from_next, 0, [&counter]() {
    ++counter;
  });
  std::int32_t j = 0;
  for (std::int32_t i = 1; i <= 5; ++i) {
    turns.end_turn();
    if (i % 2 == 0) {
      ++j;
    }
    EXPECT_EQ(counter, j);
  }
}

TEST(TurnSystem, SetCallbackAfterNRounds) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::after_n_rounds, 2,
                                            [&counter](turn_callback_info& info) {
                                              ++counter;
                                              EXPECT_TRUE(info.is_ending);
                                            });
  std::int32_t i = 1;
  for (; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 0);
  }
  turns.end_turn();
  EXPECT_EQ(counter, 1);
  for (; i <= 9; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 1);
  }
}

TEST(TurnSystem, SetCallbackAfterNTurns) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::after_n_turns, 3,
                                            [&counter](turn_callback_info& info) {
                                              ++counter;
                                              EXPECT_TRUE(info.is_ending);
                                            });
  std::int32_t i = 1;
  for (; i <= 2; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 0);
  }
  turns.end_turn();
  EXPECT_EQ(counter, 1);
  for (; i <= 9; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 1);
  }
}

TEST(TurnSystem, SetCallbackEveryTurnWithDuration) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_turn, 5,
                                            [&counter](turn_callback_info& info) {
                                              ++counter;
                                              if (counter == 5) {
                                                EXPECT_TRUE(info.is_ending);
                                              }
                                            });
  for (std::int32_t i = 1; i <= 5; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i);
  }
  for (std::int32_t i = 1; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 5);
  }
}

TEST(TurnSystem, SetCallbackEveryTwoTurnFromThisWithDuration) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_two_turns_from_this, 3,
                                            [&counter](turn_callback_info& info) {
                                              ++counter;
                                              if (counter == 3) {
                                                EXPECT_TRUE(info.is_ending);
                                              }
                                            });
  std::int32_t j = 0;
  for (std::int32_t i = 1; i <= 6; ++i) {
    turns.end_turn();
    if (i % 2 != 0) {
      ++j;
    }
    EXPECT_EQ(counter, j);
  }
  for (std::int32_t i = 1; i <= 6; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 3);
  }
}

TEST(TurnSystem, SetCallbackEveryTwoTurnFromNextWithDuration) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_two_turns_from_next, 3,
                                            [&counter](turn_callback_info& info) {
                                              ++counter;
                                              if (counter == 3) {
                                                EXPECT_TRUE(info.is_ending);
                                              }
                                            });
  std::int32_t j = 0;
  for (std::int32_t i = 1; i <= 6; ++i) {
    turns.end_turn();
    if (i % 2 == 0) {
      ++j;
    }
    EXPECT_EQ(counter, j);
  }
  for (std::int32_t i = 1; i <= 6; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 3);
  }
}

TEST(TurnSystem, Disconnect) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_turn, 0, [&counter]() {
    ++counter;
  });
  for (int i = 1; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i);
  }
  turn_connection.disconnect();
  for (int i = 1; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 3);
  }
}

TEST(TurnSystem, DisconnectOnScopeExit) {
  std::int32_t counter = 0;
  turn_system turns;
  {
    auto turn_connection = turns.set_callback(frequency_types::every_turn, 0, [&counter]() {
      ++counter;
    });
    for (int i = 1; i <= 3; ++i) {
      turns.end_turn();
      EXPECT_EQ(counter, i);
    }
  }
  for (int i = 1; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, 3);
  }
}

TEST(TurnSystem, Release) {
  std::int32_t counter = 0;
  turn_system turns;
  {
    auto turn_connection = turns.set_callback(frequency_types::every_turn, 0, [&counter]() {
      ++counter;
    });
    for (int i = 1; i <= 3; ++i) {
      turns.end_turn();
      EXPECT_EQ(counter, i);
    }
    turn_connection.release();
  }
  for (int i = 4; i <= 6; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i);
  }
}

TEST(TurnSystem, DisconnectFromCallback) {
  std::int32_t counter = 0;
  turn_system turns;
  auto turn_connection = turns.set_callback(frequency_types::every_turn, 0, [&counter](turn_callback_info& info) {
    ++counter;
    if (counter == 3) {
      info.connection.disconnect();
    }
  });
  for (int i = 1; i <= 3; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i);
  }
  turns.end_turn();
  EXPECT_EQ(counter, 3);
}

TEST(TurnSystem, OnTurn) {
  std::int32_t counter = 0;
  turn_system turns;
  turns.on_turn(3, [&counter]() {
    ++counter;
  });
  turns.on_turn(6, [&counter]() {
    ++counter;
  });
  for (std::int32_t i = 1; i <= 7; ++i) {
    turns.end_turn();
    EXPECT_EQ(counter, i / 3);
  }
}
