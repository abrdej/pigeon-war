add_library(monk SHARED
  magic_bullet.cpp
  monk.cpp)
target_link_libraries(monk turn_based)
target_include_directories(monk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
