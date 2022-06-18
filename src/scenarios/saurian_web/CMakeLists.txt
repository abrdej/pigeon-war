add_library(saurian_web SHARED
  saurian_web_scenario.cpp)
target_link_libraries(saurian_web turn_based)
target_include_directories(saurian_web PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
