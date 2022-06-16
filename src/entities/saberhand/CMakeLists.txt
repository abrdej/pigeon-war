add_library(saberhand SHARED
  saberhand.cpp
  invisibility.cpp
  sabers.cpp)
target_link_libraries(saberhand game_core)
