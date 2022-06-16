add_library(shooter SHARED
  shooter.cpp
  shoot.cpp
  grenade.cpp)
target_link_libraries(shooter game_core)
