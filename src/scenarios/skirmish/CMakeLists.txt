add_library(skirmish SHARED
  skirmish.cpp)
target_link_libraries(skirmish turn_based)
target_include_directories(skirmish PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
