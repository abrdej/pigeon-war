add_library(saurian SHARED
  saurian.cpp
  saurian_ai.cpp
  tongue_of_fire.cpp
  saurian_web.cpp)
target_link_libraries(saurian turn_based)
target_include_directories(saurian PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
