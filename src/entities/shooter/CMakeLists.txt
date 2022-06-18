add_library(shooter SHARED
  shooter.cpp
  shoot.cpp
  grenade.cpp)
target_link_libraries(shooter turn_based)
target_include_directories(shooter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
