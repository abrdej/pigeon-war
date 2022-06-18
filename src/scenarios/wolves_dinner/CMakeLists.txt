add_library(wolves_dinner SHARED
  wolves_dinner.cpp)
target_link_libraries(wolves_dinner turn_based)
target_include_directories(wolves_dinner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
