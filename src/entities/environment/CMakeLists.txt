add_library(environment SHARED
  environment.cpp)
target_link_libraries(environment game_core)
