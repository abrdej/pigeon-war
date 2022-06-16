add_library(saurian SHARED
  saurian.cpp
  tongue_of_fire.cpp
  saurian_web.cpp)
target_link_libraries(saurian game_core)
