add_library(samurai_rat SHARED
  dodge.cpp
  samurai_rat.cpp
  sword_blow.cpp)
target_link_libraries(samurai_rat turn_based)
target_include_directories(samurai_rat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
