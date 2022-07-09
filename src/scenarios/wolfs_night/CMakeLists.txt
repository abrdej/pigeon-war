add_library(wolfs_night SHARED
  wolfs_night.cpp)
target_link_libraries(wolfs_night turn_based)
target_include_directories(wolfs_night PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
