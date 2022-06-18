add_library(turn_based SHARED
  ai/action_makers.cpp
  ai/ai_manager.cpp
  ai/movers.cpp
  ai/target_finders.cpp
  ai_factory.cpp
  board.cpp
  components/applied_effects.cpp
  components/damage_taker.cpp
  components/modification.cpp
  configurable.cpp
  damage_dealers.cpp
  entities_factory.cpp
  game.cpp
  game_controller.cpp
  logger.cpp
  managers/players_manager.cpp
  messages/massages_makers.cpp
  moveable.cpp
  path_finder.cpp
  scenario_factory.cpp
  sender.cpp
  turn_system.cpp)
target_include_directories(turn_based PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
target_link_libraries(turn_based PUBLIC Boost::headers Boost::system Boost::log pthread dl)

enable_testing()

add_executable(turn_based_test board_container_test.cpp)
target_link_libraries(turn_based_test gtest gtest_main turn_based pthread)
