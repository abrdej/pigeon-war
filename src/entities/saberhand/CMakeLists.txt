add_library(saberhand SHARED
  saberhand.cpp
  invisibility.cpp
  sabers.cpp)
target_link_libraries(saberhand turn_based)
target_include_directories(saberhand PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
