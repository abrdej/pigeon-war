add_library(turn_based SHARED
  ai/action_makers.cpp
  ai/ai_manager.cpp
  ai/movers.cpp
  ai/target_finders.cpp
  ai_factory.cpp
  board.cpp
  board_helpers.cpp
  components/applied_effects.cpp
  components/damage_taker.cpp
  components/modification.cpp
  creator_helper.cpp
  damage_dealers.cpp
  entities_factory.cpp
  entities_reader.cpp
  game.cpp
  game_controller.cpp
  managers/players_manager.cpp
  map_reader.cpp
  messages/massages_makers.cpp
  move.cpp
  path_finder.cpp
  scenario_factory.cpp
  sender.cpp
  turn_system.cpp)

target_include_directories(turn_based PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
target_link_libraries(turn_based PUBLIC logging Boost::headers Boost::system pthread dl type_safe)

enable_testing()

add_executable(turn_based_test
  board_container_test.cpp
  caster_target_ability_test.cpp
  diagonal_target_ability_test.cpp
  directed_target_ability_test.cpp
  neighboring_target_ability_test.cpp
  path_target_ability_test.cpp
  per_turn_usable_test.cpp
  straight_target_ability_test.cpp
  turn_system_test.cpp
  testing/compare.cpp)
target_link_libraries(turn_based_test gtest gtest_main turn_based pthread)
