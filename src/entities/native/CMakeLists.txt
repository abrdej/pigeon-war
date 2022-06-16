add_library(native SHARED
  counterattack.cpp
  drain.cpp
  native.cpp)
target_link_libraries(native game_core)
