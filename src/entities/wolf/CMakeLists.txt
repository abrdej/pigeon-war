add_library(wolf SHARED
  claws.cpp
  wolf.cpp
  wolf_ai.cpp)
target_link_libraries(wolf turn_based)
target_include_directories(wolf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
