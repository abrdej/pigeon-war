add_library(golem SHARED
  golem.cpp
  power_bullet.cpp
  stone_skin.cpp)
target_link_libraries(golem turn_based)
target_include_directories(golem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
