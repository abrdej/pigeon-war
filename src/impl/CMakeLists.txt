add_library(impl SHARED
  game_state/get_button_description.cpp
  game_state/get_effect_description.cpp
  game_state/get_entities.cpp
  game_state/get_entity_names.cpp
  game_state/get_game_state.cpp
  scenarios/creator_helper.cpp
  scenarios/entities_reader.cpp
  scenarios/map_reader.cpp
  scenarios/saurian_web_scenario.cpp
  )
target_include_directories(impl PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
target_link_libraries(impl PRIVATE turn_based)
