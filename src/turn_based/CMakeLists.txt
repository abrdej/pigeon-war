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
  messages/messages_makers.cpp
  move.cpp
  path_finder.cpp
  scenario_factory.cpp
  sender.cpp
  turn_system.cpp)

target_include_directories(turn_based PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
target_link_libraries(turn_based PUBLIC logging Boost::headers Boost::system pthread dl type_safe)

enable_testing()

add_tests(turn_based_test)
